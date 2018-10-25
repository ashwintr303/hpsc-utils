#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sched.h>
#include <stdint.h>
#include <stdarg.h>

#include "mailbox-map.h"

#define SELECT // if not defined, then poll explicitly

#define MASTER_ID_TRCH_CPU  0x2d

#define MASTER_ID_RTPS_CPU0 0x2e
#define MASTER_ID_RTPS_CPU1 0x2f

#define MASTER_ID_HPPS_CPU0 0x80
#define MASTER_ID_HPPS_CPU1 0x8d
#define MASTER_ID_HPPS_CPU2 0x8e
#define MASTER_ID_HPPS_CPU3 0x8f
#define MASTER_ID_HPPS_CPU4 0x90
#define MASTER_ID_HPPS_CPU5 0x9d
#define MASTER_ID_HPPS_CPU6 0x9e
#define MASTER_ID_HPPS_CPU7 0x9f

#define HPSC_MBOX_DATA_REGS 16

// From TRCH/RTPS command.h
#define CMD_ECHO                        0x1
#define CMD_NOP                         0x2
#define CMD_RESET_HPPS                  0x3
#define CMD_MBOX_LINK_CONNECT           0x4
#define CMD_MBOX_LINK_DISCONNECT        0x5
#define CMD_MBOX_LINK_ECHO              0x6

#define ENDPOINT_HPPS 0
#define ENDPOINT_RTPS 1

#define DEV_PATH_DIR "/dev/"
#define DEV_FILE_PREFIX "mbox"

#define PATH_SIZE 128

static char devpath_out_buf[PATH_SIZE];
static char devpath_in_buf[PATH_SIZE];
static char devpath_own_out_buf[PATH_SIZE];
static char devpath_own_in_buf[PATH_SIZE];

#define MSG_SIZE HPSC_MBOX_DATA_REGS
static uint32_t msg[HPSC_MBOX_DATA_REGS] = {0};

static int fd_out = -1, fd_in = -1, fd_own_out = -1, fd_own_in = -1;

static void print_msg(const char *ctx, uint32_t *reply, size_t len)
{
    unsigned i;
    printf("%s: ", ctx);
    for (i = 0; i < len; ++i) {
        printf("%x ", reply[i]);
    }
    printf("\n");
}

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

static const char *cmd_to_string(unsigned cmd)
{
        switch (cmd) {
                case CMD_ECHO:                 return "ECHO";
                case CMD_NOP:                  return "NOP";
                case CMD_RESET_HPPS:           return "RESET_HPPS";
                case CMD_MBOX_LINK_CONNECT:    return "CMD_MBOX_LINK_CONNECT";
                case CMD_MBOX_LINK_DISCONNECT: return "CMD_MBOX_LINK_DISCONNECT";
                case CMD_MBOX_LINK_ECHO:       return "CMD_MBOX_LINK_ECHO";
                default: return "?";
        }
}

static int mbox_open(const char *path, int dir_flag)
{
    int fd = open(path, dir_flag | O_NONBLOCK);
    if (fd < 0) {
        fprintf(stderr, "error: open '%s' failed: %s\n", path, strerror(errno));
        exit(1);
    }
    return fd;
}

static void mbox_close(int fd)
{
    if (fd < 0)
        return;
    int rc = close(fd);
    if (rc < 0)
        fprintf(stderr, "error: close failed: %s\n", strerror(errno));
}

static int mbox_read(int fd)
{
    int rc;
#ifdef SELECT
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(fd, &fds);

    printf("select\n");
    rc = select(1, &fds, NULL, NULL, /* timeout */ NULL);
    if (rc <= 0) {
        fprintf(stderr, "error: select failed: %s\n", strerror(errno));
        return -1;
    }

    rc = read(fd, msg, sizeof(msg)); // non-blocking
    if (rc < 0) {
        fprintf(stderr, "error: read failed: %s\n", strerror(errno));
        return -1;
    }
#else // !SELECT
    do {
        rc = read(fd, msg, sizeof(msg)); // non-blocking
        if (rc < 0) {
            if (errno != EAGAIN) {
                fprintf(stderr, "error: read failed: %s\n", strerror(errno));
                return -1;
            }
            sleep(1);
        }
    } while (rc < 0);
#endif // !SELECT
    return 0;
}

static int mbox_write(int fd)
{
    int rc = -1;
    unsigned i;

    rc = write(fd, msg, sizeof(msg));
    if (rc != sizeof(msg)) {
        fprintf(stderr, "error: write failed: %s\n", strerror(errno));
        return rc;
    }

    // poll for ack of our outgoing transmission by remote side
    //
    // NOTE: This wait is needed between back-to-back messages, because
    // The wait the kernel on the remote receiver sidd has a buffer of size 1
    // message only, and an ACK from that receiver indicates that its buffer is
    // empty and so can receive the next message.
    //
    // In this test case, we send a NOP (which generates no reply)
    // follow by an ECHO. After NOP before ECHO, we have to wait for ACK.
    // After ACK for NOP comes, we can send ECHO. After ECHO, we can
    // optionally wait for ACK, or just wait for the reply.

    rc = mbox_read(fd);
    if (rc < 0)
        return rc;

    printf("received ACK\r\n");

    return 0;
}

static int _mbox_request(unsigned cmd, unsigned nargs, va_list va)
{
    unsigned i;

    printf("sending command: cmd %s\n", cmd_to_string(cmd));

    msg[0] = cmd;
    for (i = 0; i < nargs && i < MSG_SIZE; ++i)
        msg[i + 1] = va_arg(va, unsigned); 

    return mbox_write(fd_out);
}

static int mbox_request(unsigned cmd, unsigned nargs, ...)
{
    va_list va;
    va_start(va, nargs);
    int rc = _mbox_request(cmd, nargs, va);
    va_end(va);
    return rc;
}

static int mbox_rpc(unsigned cmd, unsigned nargs, ...)
{
    va_list va;
    va_start(va, nargs);

    int rc;

    rc = _mbox_request(cmd, nargs, va);
    if (rc)
        goto cleanup;

    rc = mbox_read(fd_in);
    if (rc)
        goto cleanup;

    print_msg("RPC reply: ", msg, MSG_SIZE);

    rc = 0;

cleanup:
    va_end(va);
    return rc;
}

int main(int argc, char **argv) {
    const char *devpath_out, *devpath_in;
    const char *devpath_own_out, *devpath_own_in;
    int cpu = -1; // by default don't pin
    unsigned ret = 0;
    int rc, status;
    unsigned i;
    bool test_own = false;

    if (argc == 1) {
        devpath_out = "0";
        devpath_in = "1";
    } else if (argc == 3 || argc == 5) {
        devpath_out = argv[1];
        devpath_in = argv[2];
        if (argc == 5) {
            devpath_own_out = argv[3];
            devpath_own_in = argv[4];
            test_own = true;
        }
    } else {
        fprintf(stderr, "usage: %s [out_mbox_path|filename|index in_mbox_path|filename|index  [mbox_own_out mbox_own_in]]\n", argv[0]);
        return 1;
    }

    devpath_out = expand_path(devpath_out, devpath_out_buf, sizeof(devpath_out_buf));
    devpath_in = expand_path(devpath_in, devpath_in_buf, sizeof(devpath_in_buf));
    if (test_own) {
        devpath_own_out = expand_path(devpath_own_out, devpath_own_out_buf, sizeof(devpath_own_out_buf));
        devpath_own_in = expand_path(devpath_own_in, devpath_own_in_buf, sizeof(devpath_own_in_buf));
    }

    if (!(devpath_out && devpath_in)) {
        fprintf(stderr, "error: failed to construct path\n");
        return 1;
    }

    printf("out mbox: %s\n", devpath_out);
    printf(" in mbox: %s\n", devpath_in);

    if (test_own) {
        printf("out mbox: %s\n", devpath_own_out);
        printf(" in mbox: %s\n", devpath_own_in);
    }

    if (cpu > 0) {
        // pin to core
        cpu_set_t cpumask;
        CPU_ZERO(&cpumask);
        CPU_SET(cpu, &cpumask);
        sched_setaffinity(0 /* i.e. self */, sizeof(cpu_set_t), &cpumask);
    }

    fd_out = mbox_open(devpath_out, O_RDWR); // read gets us the [N]ACK
    fd_in = mbox_open(devpath_in, O_RDONLY);

    if (test_own) {
        fd_own_out = mbox_open(devpath_own_out, O_RDWR); // read gets us the [N]ACK
        fd_own_in = mbox_open(devpath_own_in, O_RDONLY);
    }

    if (mbox_request(CMD_NOP, 0)) // no reply
        goto cleanup;

    if (mbox_rpc(CMD_ECHO, 1, 42))
        goto cleanup;

    print_msg("reply to ECHO: ", msg, MSG_SIZE);

    // Test where Linux is the owner and TRCH is destination (opposite setup
    // from the above test).
    //
    // The '_own_' mailboxes are marked with owner=Linux and destination=TRCH
    // in Linux device tree. When we open these two mailboxes above, they are
    // claimed, and after this TRCH can open them as destination (as opposed to
    // owner, as for the first pair of mailboxes).
    //
    // We ask TRCH to open the mailboxes as destination with MBOX_LINK_CONNECT
    // (via the first pair of mailboxes owned by TRCH). We then ask TRCH to
    // send us a request (via the '_own_' mailboxes).  We handle the request as
    // an ECHO command and reply back (via the '_own_' mailboxes).
    if (test_own) {
        int link = mbox_rpc(CMD_MBOX_LINK_CONNECT, 3, ENDPOINT_HPPS,
                            MBOX_HPPS_HPPS_OWN_TRCH, MBOX_HPPS_TRCH_HPPS_OWN);
        if (link < 0)
            goto cleanup;

        // must not block because TRCH waits for our reply, so not mbox_rpc
        if (mbox_request(CMD_MBOX_LINK_ECHO, 1, link))
            goto cleanup;


        rc = mbox_read(fd_own_in);
        if (rc)
            goto cleanup;
        print_msg("request: ECHO: ", msg, MSG_SIZE);

        // send what we received
        rc = mbox_write(fd_own_out);
        if (rc)
            goto cleanup;


        // read reply to CMD_MBOX_LINK_ECHO request
        rc = mbox_read(fd_in);
        if (rc)
            goto cleanup;

        if (mbox_rpc(CMD_MBOX_LINK_DISCONNECT, link))
            goto cleanup;
    }

     return 0;

cleanup:
    mbox_close(fd_out);
    mbox_close(fd_in);
    if (test_own) {
        mbox_close(fd_own_out);
        mbox_close(fd_own_in);
    }
    return rc;
}
