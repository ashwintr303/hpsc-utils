#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/epoll.h>
#include "mbox.h"

int mbox_open(struct mbox *mbox, const char *path, int flags)
{
    mbox->fd = open(path, flags | O_NONBLOCK);
    return mbox->fd < 0 ? -1 : 0;
}

int mbox_close(struct mbox *mbox)
{
    return mbox->fd < 0 ? 0 : close(mbox->fd);
}

int mbox_set_notif_type(struct mbox *mbox, enum mbox_notif notif_type)
{
    switch (notif_type) {
    case MBOX_NOTIF_NONE:
    case MBOX_NOTIF_SELECT:
    case MBOX_NOTIF_POLL:
    case MBOX_NOTIF_EPOLL:
        mbox->notif_type = notif_type;
        return 0;
    }
    errno = EINVAL;
    return -1;
}

int mbox_set_timeout_ms(struct mbox *mbox, int timeout_ms)
{
    mbox->timeout_ms = timeout_ms;
    return 0;
}

ssize_t mbox_write(struct mbox *mbox)
{
    return write(mbox->fd, mbox->data.bytes, sizeof(mbox->data.bytes));
}

static ssize_t mbox_do_read(struct mbox *mbox)
{
    // non-blocking
    return read(mbox->fd, mbox->data.bytes, sizeof(mbox->data.bytes));
}

static ssize_t mbox_read_none(struct mbox *mbox)
{
    int to_ms_rem = mbox->timeout_ms;
    ssize_t rc;
    do {
        rc = mbox_do_read(mbox);
        if (rc < 0) {
            // EAGAIN is expected, any other error is a problem
            if (errno != EAGAIN) {
                return rc;
            }
            if (!to_ms_rem) {
                return 0; // timeout
            }
            usleep(1000);
            if (to_ms_rem > 0) {
                // to_ms_rem < 0 indicates infinite timeout
                to_ms_rem--;
            }
        }
    } while (rc < 0);
    return rc;
}

static ssize_t mbox_read_select(struct mbox *mbox)
{
    ssize_t rc;
    fd_set fds;
    struct timeval tv;
    struct timeval *to;
    FD_ZERO(&fds);
    FD_SET(mbox->fd, &fds);
    tv.tv_sec = mbox->timeout_ms / 1000;
    tv.tv_usec = (mbox->timeout_ms % 1000) * 1000;
    to = mbox->timeout_ms >= 0 ? &tv : NULL;
    rc = select(mbox->fd + 1, &fds, NULL, NULL, to);
    if (rc < 0) {
        perror("select");
        return rc;
    }
    if (rc > 0) {
        return mbox_do_read(mbox);
    }
    return 0; // timeout
}

static ssize_t mbox_read_poll(struct mbox *mbox)
{
    struct pollfd fds[1] = { { .fd = mbox->fd, .events = POLLIN } };
    ssize_t rc = poll(fds, 1, mbox->timeout_ms);
    if (rc < 0) {
        perror("poll");
        return rc;
    }
    if (rc > 0) {
        return mbox_do_read(mbox);
    }
    return 0; // timeout
}

static ssize_t mbox_read_epoll(struct mbox *mbox)
{
    ssize_t rc;
    int err = 0;
    struct epoll_event events[1];
    struct epoll_event ev = { .events = EPOLLIN, .data.fd = mbox->fd };
    // timeout must be -1 to block indefinitely, see epoll_wait(2)
    int timeout_ms = mbox->timeout_ms < -1 ? -1 : mbox->timeout_ms;
    int epfd = epoll_create(1);
    if (epfd < 0) {
        perror("epoll_create");
        return -1;
    }
    rc = epoll_ctl(epfd, EPOLL_CTL_ADD, mbox->fd, &ev);
    if (rc < 0) {
        perror("epoll_ctl");
        goto out;
    }
    rc = epoll_wait(epfd, events, 1, timeout_ms);
    if (rc < 0) {
        perror("epoll_wait");
        goto out;
    }
    if (rc == 0) { // timeout
        goto out;
    }
    if (events[0].data.fd != mbox->fd || !(events[0].events & EPOLLIN)) {
        fprintf(stderr, "epoll_wait: unexpected return\n");
        errno = EIO;
    }
out:
    err = errno;
    close(epfd);
    errno = err; // reclaim errno if close reset it
    return rc <= 0 ? rc : mbox_do_read(mbox);
}

ssize_t mbox_read(struct mbox *mbox)
{
    switch (mbox->notif_type) {
    case MBOX_NOTIF_NONE:
        return mbox_read_none(mbox);
    case MBOX_NOTIF_SELECT:
        return mbox_read_select(mbox);
    case MBOX_NOTIF_POLL:
        return mbox_read_poll(mbox);
    case MBOX_NOTIF_EPOLL:
        return mbox_read_epoll(mbox);
    }
    // shouldn't happen unless user overrides notif_type manually
    errno = EINVAL;
    return -1;
}

ssize_t mbox_read_ack(struct mbox *mbox)
{
    switch (mbox->notif_type) {
    case MBOX_NOTIF_NONE:
        return mbox_read_none(mbox);
    case MBOX_NOTIF_SELECT:
        return mbox_read_select(mbox);
    case MBOX_NOTIF_POLL:
        return mbox_read_poll(mbox);
    case MBOX_NOTIF_EPOLL:
        return mbox_read_epoll(mbox);
    }
    // shouldn't happen unless user overrides notif_type manually
    errno = EINVAL;
    return -1;
}
