#ifndef MBOX_H
#define MBOX_H

#include <stdint.h>
#include <stdlib.h>

/* The HPSC Chiplet mailboxes are 64 bytes */
#define MBOX_SIZE 64

/**
 * Options for notification support
 */
enum mbox_notif {
    MBOX_NOTIF_NONE = 0,
    MBOX_NOTIF_SELECT,
    MBOX_NOTIF_POLL,
    MBOX_NOTIF_EPOLL
};

struct mbox {
    union {
        uint8_t bytes[MBOX_SIZE];
        uint32_t ack;
    } data;
    int fd;
    enum mbox_notif notif_type;
    int timeout_ms; // -1 = infinite, 0 = no timeout
};

/**
 * Open a mailbox device file. 
 * The O_NONBLOCK flag is automatically applied.
 *
 * @param mbox the mailbox context struct
 * @param path the path the device file, e.g., /dev/mbox/0/mbox0
 * @param flags the open flags
 * @return 0 on success, -1 failure (see open(2) for errno values)
 */
int mbox_open(struct mbox *mbox, const char *path, int flags);

/**
 * Set the notification type for read support.
 *
 * @param mbox
 * @param notif_type
 * @return 0 on success, -1 failure and errno set to EINVAL
 */
int mbox_set_notif_type(struct mbox *mbox, enum mbox_notif notif_type);

/**
 * Set the timeout to use when waiting to read.
 * Positive value for timeout, 0 for no timeout, or -1 for infinite timeout.
 *
 * @param mbox
 * @param timeout_ms
 * @return 0 on success, -1 failure and errno set to EINVAL
 */
int mbox_set_timeout_ms(struct mbox *mbox, int timeout_ms);

/**
 * Send the message stored in the mbox's data field.
 *
 * @param mbox
 * @return see write(2)
 */
ssize_t mbox_write(struct mbox *mbox);

/**
 * Read a message in the mbox's data field.
 * In addition to return values below, errno is set to ETIME on timeout.
 *
 * @param mbox
 * @return see read(2), select(2), epoll_create(2), epoll_ctl(2), epoll_wait(2)
 */
ssize_t mbox_read(struct mbox *mbox);

/**
 * Read a sent message's ACK in the mbox's data field.
 * In addition to return values below, errno is set to ETIME on timeout.
 *
 * @param mbox
 * @return see read(2), select(2), epoll_create(2), epoll_ctl(2), epoll_wait(2)
 */
ssize_t mbox_read_ack(struct mbox *mbox);

/**
 * Close an open mailbox.
 *
 * @param mbox
 * @return see close(2)
 */
int mbox_close(struct mbox *mbox);

#endif // MBOX_H
