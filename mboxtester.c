#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sched.h>
#include <stdint.h>

#define HPSC_MBOX_DATA_REGS 16

// From TRCH command.h
#define CMD_ECHO       0x1
#define CMD_RESET_HPPS 0x3

#define DEV_PATH_DIR "/dev/"
#define DEV_FILE_PREFIX "mbox"

static char devpath_out_buf[128];
static char devpath_in_buf[128];

static const char *expand_path(const char *path, char *buf, size_t size)
{
        ssize_t sz = size;
        if (path[0] != '/') {
                buf[0] = '\0';
                if (sz <= 0)
                        return NULL;
                strncat(buf, DEV_PATH_DIR, sz - 1);
                sz -= strlen(DEV_PATH_DIR);

                if ('0' <= path[0] && path[0] <= '9') {
                        if (sz <= 0)
                                return NULL;
                       strncat(buf, DEV_FILE_PREFIX, sz - 1);
                       size -= strlen(DEV_FILE_PREFIX);
                }
                if (sz <= 0)
                        return NULL;
                strncat(buf, path, sz - 1);
                return buf;
        } else {
                return path;
        }
}

int main(int argc, char **argv) {
    const char *devpath_out, *devpath_in;
    int cpu = -1; // by default don't pin
    unsigned ret = 0;
    int rc;
    unsigned i;

    if (argc == 1) {
        devpath_out = "0";
        devpath_in = "1";
    } else if (argc == 3 || argc == 4) {
        devpath_out = argv[1];
        devpath_in = argv[2];
        if (argc == 4)
            cpu = atoi(argv[3]);
    } else {
        fprintf(stderr, "usage: %s [out_mbox_path|filename|index in_mbox_path|filename|index [cpu]]\n", argv[0]);
        return 1;
    }

    devpath_out = expand_path(devpath_out, devpath_out_buf, sizeof(devpath_out_buf));
    devpath_in = expand_path(devpath_in, devpath_in_buf, sizeof(devpath_in_buf));

    if (!(devpath_out && devpath_in)) {
        fprintf(stderr, "error: failed to construct path\n");
        return 1;
    }

    printf("out mbox: %s\n", devpath_out);
    printf(" in mbox: %s\n", devpath_in);

    if (cpu > 0) {
        // pin to core
        cpu_set_t cpumask;
        CPU_ZERO(&cpumask);
        CPU_SET(cpu, &cpumask);
        sched_setaffinity(0 /* i.e. self */, sizeof(cpu_set_t), &cpumask);
    }

    int fd_out = open(devpath_out, O_RDWR | O_NONBLOCK); // read gets us the [N]ACK
    if (fd_out < 0) {
        fprintf(stderr, "error: open '%s' failed: %s\n", devpath_out, strerror(errno));
        return 1;
    }

    int fd_in = open(devpath_in, O_RDONLY | O_NONBLOCK);
    if (fd_in < 0) {
        fprintf(stderr, "error: open '%s' failed: %s\n", devpath_in, strerror(errno));
        return 1;
    }

    uint32_t msg[HPSC_MBOX_DATA_REGS] = { CMD_ECHO, 42 };
    rc = write(fd_out, msg, sizeof(msg[0]) * HPSC_MBOX_DATA_REGS);
    if (rc != sizeof(msg)) {
        fprintf(stderr, "error: write failed: %s\n", strerror(errno));
        return 1;
    }

    // poll for ack of our outgoing transmission by remote side
    //
    // NOTE: this is optional, we can just wait for reply, but if we want to
    // send back-to back messages (e.g. a sequence of messages that generates
    // one reply), then we must wait for ACK before sending each next message,
    // because the kernel on the remote receiver sidd has a buffer of size 1
    // message only, and an ACK from that receiver indicates that its buffer is
    // empty and so can receive the next message.

    int status;
    do {
        rc = read(fd_out, &status, sizeof(status)); // non-blocking
        if (rc < 0) {
            if (errno != EAGAIN) {
                fprintf(stderr, "error: read failed: %s\n", strerror(errno));
                goto cleanup;
            }
            sleep(1);
        }
    } while (rc < 0);

    printf("received ACK for our outgoing message: status %d\r\n", status);

    // poll for reply
    do {
        rc = read(fd_in, msg, sizeof(msg)); // non-blocking
        if (rc < 0) {
            if (errno != EAGAIN) {
                fprintf(stderr, "error: read failed: %s\n", strerror(errno));
                goto cleanup;
            }
            sleep(1);
        }
    } while (rc < 0);

    printf("reply: ");
    for (i = 0; i < rc / sizeof(msg[0]); ++i) {
        printf("%x ", msg[i]);
    }
    printf("\n");

cleanup:
    rc = close(fd_out);
    if (rc) {
        fprintf(stderr, "error: close out '%s' failed: %s\n", devpath_out, strerror(errno));
        ret = 1;
    }

    rc = close(fd_in);
    if (rc) {
        fprintf(stderr, "error: close in '%s' in failed: %s\n", devpath_in, strerror(errno));
        ret = 1;
    }
    return ret;
}
