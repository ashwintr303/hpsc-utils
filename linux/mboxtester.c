#define _GNU_SOURCE

#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <sched.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mailbox-map.h"
#include "libmbox/mbox.h"

// From TRCH/RTPS command.h
#define CMD_NOP                         0
#define CMD_PING                        1
#define CMD_PONG                        2
#define CMD_MBOX_LINK_CONNECT           1000
#define CMD_MBOX_LINK_DISCONNECT        1001
#define CMD_MBOX_LINK_PING              1002

#define ENDPOINT_HPPS 0
#define ENDPOINT_RTPS 1

#define DEV_PATH_DIR "/dev/mbox/0/"
#define DEV_FILE_PREFIX "mbox"

#define PATH_SIZE 128

static struct mbox mbox_out;
static struct mbox mbox_in;
static struct mbox mbox_own_out;
static struct mbox mbox_own_in;

static enum mbox_notif notif_type = MBOX_NOTIF_NONE;
static int timeout_ms = -1;

// these align with enum mbox_notif
static const char* const NOTIF_TYPE_NAMES[] = {
    "none",
    "select",
    "poll",
    "epoll"
};

static void print_msg(const char *ctx, uint32_t *msg, size_t len)
{
    size_t i;
    printf("%s: ", ctx);
    for (i = 0; i < len; ++i) {
        printf("%02x ", msg[i]);
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
        }
        return path;
}

static const char *cmd_to_str(uint32_t cmd)
{
    switch (cmd) {
        case CMD_NOP:                  return "NOP";
        case CMD_PING:                 return "PING";
        case CMD_PONG:                 return "PONG";
        case CMD_MBOX_LINK_CONNECT:    return "MBOX_LINK_CONNECT";
        case CMD_MBOX_LINK_DISCONNECT: return "MBOX_LINK_DISCONNECT";
        case CMD_MBOX_LINK_PING:       return "MBOX_LINK_PING";
        default:                       return "?";
    }
}

static ssize_t mboxtester_write_ack(struct mbox *mbox)
{
    ssize_t rc_ack;
    ssize_t rc;
    printf("Write command: %s\n", cmd_to_str(mbox->data.regs[0]));
    print_msg("mbox_write", mbox->data.regs, MBOX_REGS);
    rc = mbox_write(mbox);
    // we always write the whole buffer
    if (rc < 0) {
        perror("mbox_write");
        return rc;
    }
    if (rc != MBOX_SIZE) {
        fprintf(stderr, "mbox_write: rc != MBOX_SIZE?\n");
        errno = -EIO;
        return -1;
    }
    // poll for ack of our outgoing transmission by remote side
    //
    // NOTE: This wait is needed between back-to-back messages, because
    // The wait the kernel on the remote receiver side has a buffer of size 1
    // message only, and an ACK from that receiver indicates that its buffer is
    // empty and so can receive the next message.
    rc_ack = mbox_read_ack(mbox);
    if (rc_ack < 0) {
        perror("mbox_read_ack");
        return rc_ack;
    }
    if (!rc_ack) {
        return -1; // timeout reading ACK
    }
    print_msg("mbox_read_ack", &mbox->data.ack, 1);
    return rc;
}

static ssize_t mboxtester_read(struct mbox *mbox)
{
    ssize_t rc = mbox_read(mbox);
    if (!rc) {
        return -1; // timeout
    }
    if (rc > 0) {
        print_msg("mbox_read", mbox->data.regs, MBOX_REGS);
        printf("Read command: %s\n", cmd_to_str(mbox->data.regs[0]));
    }
    return rc;
}

static ssize_t mbox_request_va(struct mbox *mbox, uint32_t cmd, unsigned nargs,
                                va_list va)
{
    size_t i;
    mbox->data.regs[0] = cmd;
    for (i = 1; i <= nargs && i < MBOX_REGS; ++i)
        mbox->data.regs[i] = va_arg(va, uint32_t); 
    return mboxtester_write_ack(mbox);
}

static ssize_t mbox_request(uint32_t cmd, unsigned nargs, ...)
{
    va_list va;
    va_start(va, nargs);
    ssize_t rc = mbox_request_va(&mbox_out, cmd, nargs, va);
    va_end(va);
    return rc;
}

static ssize_t mbox_rpc(uint32_t cmd, unsigned nargs, ...)
{
    va_list va;
    va_start(va, nargs);
    ssize_t rc = mbox_request_va(&mbox_out, cmd, nargs, va);
    if (rc < 0) {
        perror("mbox_rpc: mbox_request_va");
        goto cleanup;
    }
    rc = mboxtester_read(&mbox_in);
    if (rc < 0) {
        perror("mbox_rpc: mboxtester_read");
        goto cleanup;
    }
cleanup:
    va_end(va);
    return rc;
}

static void mbox_open_or_die(struct mbox *mbox, const char* path, int flags)
{
    int rc = mbox_open(mbox, path, flags);
    if (rc) {
        fprintf(stderr, "mbox_open: %s: %s\n", path, strerror(errno));
        exit(-rc);
    }
    mbox_set_notif_type(mbox, notif_type);
    mbox_set_timeout_ms(mbox, timeout_ms);
}

static void usage(const char *pname, int code)
{
    fprintf(code ? stderr : stdout,
            "Usage: %s [-o FILE] [-i FILE] [-O FILE] [-I FILE] [-n TYPE] [-t N] [-c CPU] [-h]\n"
            "  -o, --out=FILE       The outbound mailbox path, filename, or index\n"
            "                       The default value is 0, for /dev/mbox/0/mbox0\n"
            "  -i, --in=FILE        The inbound mailbox path, filename, or index\n"
            "                       The default value is 1, for /dev/mbox/0/mbox1\n"
            "  -O, --out-own=FILE   The outbound \"own\" mailbox path, filename, or index\n"
            "                       When using, must also specify -I option\n"
            "                       Off by default\n"
            "  -I, --in-own=FILE    The inbound \"own\" mailbox path, filename, or index\n"
            "                       When using, must also specify -O option\n"
            "                       Off by default\n"
            "  -n, --not-type=TYPE  Notification type, one of: none, select, poll, epoll\n"
            "                       The default value is \"none\"\n"
            "  -t, --timeout=N      Timeout for reads, in milliseconds\n"
            "                       The default value is -1 (infinite timeout)\n"
            "                       Specify a positive value, or 0 for no timeout\n"
            "  -c, --cpu=CPU        Pin process to CPU\n",
            "                       The default value is -1, for no pinning\n"
            "  -h, --help           Print this message and exit\n",
            pname);
    exit(code);
}

static const char short_options[] = "o:i:O:I:n:t:c:h";
static const struct option long_options[] = {
    {"out",         required_argument,  NULL,   'o'},
    {"in",          required_argument,  NULL,   'i'},
    {"out-own",     required_argument,  NULL,   'O'},
    {"in-own",      required_argument,  NULL,   'I'},
    {"not-type",    required_argument,  NULL,   'n'},
    {"timeout",     required_argument,  NULL,   't'},
    {"cpu",         required_argument,  NULL,   'c'},
    {"help",        no_argument,        NULL,   'h'},
    {0, 0, 0, 0}
};

int main(int argc, char **argv) {
    char devpath_out_buf[PATH_SIZE];
    char devpath_in_buf[PATH_SIZE];
    char devpath_own_out_buf[PATH_SIZE];
    char devpath_own_in_buf[PATH_SIZE];
    const char *devpath_out = "0";
    const char *devpath_in = "1";
    const char *devpath_own_out = NULL;
    const char *devpath_own_in = NULL;
    int cpu = -1;
    int rc = 0;
    ssize_t rc_req;
    bool test_own = false;
    int c;

    // parse options
    while ((c = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {
        switch (c) {
        case 'o':
            devpath_out = optarg;
            break;
        case 'i':
            devpath_in = optarg;
            break;
        case 'O':
            devpath_own_out = optarg;
            test_own = true;
            break;
        case 'I':
            devpath_own_in = optarg;
            test_own = true;
            break;
        case 'n':
            if (!strcmp(optarg, "none")) {
                notif_type = MBOX_NOTIF_NONE;
            } else if (!strcmp(optarg, "select")) {
                notif_type = MBOX_NOTIF_SELECT;
            } else if (!strcmp(optarg, "poll")) {
                notif_type = MBOX_NOTIF_POLL;
            } else if (!strcmp(optarg, "epoll")) {
                notif_type = MBOX_NOTIF_EPOLL;
            } else {
                fprintf(stderr, "Unknown notification type: %s\n", optarg);
                usage(argv[0], EINVAL);
            }
            break;
        case 't':
            timeout_ms = atoi(optarg);
            break;
        case 'c':
            cpu = atoi(optarg);
            break;
        case 'h':
            usage(argv[0], 0);
            break;
        default:
            usage(argv[0], EINVAL);
            break;
        }
    }

    printf("Config:\n");
    printf("  not-type:  %s\n", NOTIF_TYPE_NAMES[notif_type]);
    printf("  timeout:   %d\n", timeout_ms);
    printf("  cpu:       %d\n", cpu);

    devpath_out = expand_path(devpath_out, devpath_out_buf, sizeof(devpath_out_buf));
    devpath_in = expand_path(devpath_in, devpath_in_buf, sizeof(devpath_in_buf));
    if (!(devpath_out && devpath_in)) {
        fprintf(stderr, "error: failed to construct path\n");
        return 1;
    }
    printf("  out:       %s\n", devpath_out);
    printf("  in:        %s\n", devpath_in);

    if (test_own) {
        if (!devpath_own_out || !devpath_own_in) {
            fprintf(stderr, "Must specify both out and in when using own path\n");
            usage(argv[0], EINVAL);
        }
        devpath_own_out = expand_path(devpath_own_out, devpath_own_out_buf, sizeof(devpath_own_out_buf));
        devpath_own_in = expand_path(devpath_own_in, devpath_own_in_buf, sizeof(devpath_own_in_buf));
        printf("  out-own:   %s\n", devpath_own_out);
        printf("  in-own:    %s\n", devpath_own_in);
    }

    if (cpu >= 0) {
        // pin to core
        cpu_set_t cpumask;
        CPU_ZERO(&cpumask);
        CPU_SET(cpu, &cpumask);
        sched_setaffinity(0 /* i.e. self */, sizeof(cpu_set_t), &cpumask);
    }

    mbox_open_or_die(&mbox_out, devpath_out, O_RDWR); // read gets us the [N]ACK
    mbox_open_or_die(&mbox_in, devpath_in, O_RDONLY);
    if (test_own) {
        mbox_open_or_die(&mbox_own_out, devpath_own_out, O_RDWR); // read gets us the [N]ACK
        mbox_open_or_die(&mbox_own_in, devpath_own_in, O_RDONLY);
    }

    // In this test case, we send a NOP (which generates no reply)
    // follow by a PING. After NOP before PING, we have to wait for ACK.
    // After ACK for NOP comes, we can send PING. After PING, we can
    // optionally wait for ACK, or just wait for the reply.
    rc_req = mbox_request(CMD_NOP, 0); // no reply
    if (rc_req < 0) {
        perror("mbox_request: CMD_NOP");
        rc = errno;
        goto cleanup;
    }

    rc_req = mbox_rpc(CMD_PING, 1, 42);
    if (rc_req < 0) {
        perror("mbox_rpc: CMD_PING");
        rc = errno;
        goto cleanup;
    }

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
    // an PING command and reply back (via the '_own_' mailboxes).
    if (test_own) {
        rc_req = mbox_rpc(CMD_MBOX_LINK_CONNECT, 3, ENDPOINT_HPPS,
                          MBOX_HPPS_TRCH__HPPS_OWN_TRCH,
                          MBOX_HPPS_TRCH__TRCH_HPPS_OWN);
        if (rc_req < 0) {
            perror("mbox_rpc: link: CMD_MBOX_LINK_CONNECT");
            rc = errno;
            goto cleanup;
        }

        // must not block because TRCH waits for our reply, so not mbox_rpc
        rc_req = mbox_request(CMD_MBOX_LINK_PING, 1, 0);
        if (rc_req < 0) {
            perror("mbox_request: link: CMD_MBOX_LINK_PING");
            rc = errno;
            goto cleanup;
        }

        rc_req = mboxtester_read(&mbox_own_in);
        if (rc_req < 0) {
            perror("mboxtester_read: link: mbox_own_in");
            rc = errno;
            goto cleanup;
        }
        if (mbox_own_in.data.regs[0] != CMD_PING) {
            fprintf(stderr, "Expected PING, got %s\n",
                    cmd_to_str(mbox_own_in.data.regs[0]));
            rc = EIO;
            goto cleanup;
        }
        // reply to PING with PONG
        memcpy(mbox_own_out.data.regs, mbox_own_in.data.regs,
               sizeof(mbox_own_out.data.regs));
        mbox_own_out.data.regs[0] = CMD_PONG;
        rc_req = mboxtester_write_ack(&mbox_own_out);
        if (rc_req < 0) {
            perror("mboxtester_write_ack: link: mbox_own_out");
            rc = errno;
            goto cleanup;
        }

        // read reply to CMD_MBOX_LINK_PING request
        rc_req = mboxtester_read(&mbox_in);
        if (rc_req < 0) {
            perror("mboxtester_read: link: mbox_in");
            rc = errno;
            goto cleanup;
        }

        rc_req = mbox_rpc(CMD_MBOX_LINK_DISCONNECT, 1, 0);
        if (rc_req < 0) {
            perror("mbox_rpc: link: CMD_MBOX_LINK_DISCONNECT");
            rc = errno;
            goto cleanup;
        }
    }

cleanup:
    mbox_close(&mbox_out);
    mbox_close(&mbox_in);
    if (test_own) {
        mbox_close(&mbox_own_out);
        mbox_close(&mbox_own_in);
    }
    return rc;
}
