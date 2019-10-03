#define _GNU_SOURCE

#include <errno.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mailbox-map.h"
#include "libmbox/mbox.h"

#include "mbox-utils.h"

#define DEV_PATH_DIR "/dev/mbox/0/"
#define DEV_FILE_PREFIX "mbox"

static void print_msg(const char *ctx, void *msg, size_t sz)
{
    uint32_t *msg_u32 = (uint32_t *)msg;
    size_t len = sz / sizeof(uint32_t);
    size_t i;
    printf("%s: ", ctx);
    for (i = 0; i < len; ++i) {
        printf("%02x ", msg_u32[i]);
    }
    printf("\n");
}

const char *expand_path(const char *path, char *buf, size_t size)
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

const char *cmd_to_str(uint8_t cmd)
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

ssize_t mboxtester_write_ack(struct mbox *mbox)
{
    ssize_t rc_ack;
    ssize_t rc;
    printf("Write command: %s\n", cmd_to_str(mbox->data.bytes[0]));
    print_msg("mbox_write", mbox->data.bytes, sizeof(mbox->data.bytes));
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

ssize_t mboxtester_read(struct mbox *mbox)
{
    ssize_t rc = mbox_read(mbox);
    if (!rc) {
        return -1; // timeout
    }
    if (rc > 0) {
        print_msg("mbox_read", mbox->data.bytes, sizeof(mbox->data.bytes));
        printf("Read command: %s\n", cmd_to_str(mbox->data.bytes[0]));
    }
    return rc;
}

static ssize_t mbox_request_va(struct mbox *mbox, uint8_t cmd, unsigned nargs,
                               va_list va)
{
    size_t i;
    mbox->data.bytes[0] = cmd;
    mbox->data.bytes[1] = 0;
    mbox->data.bytes[2] = 0;
    mbox->data.bytes[3] = 0;
    // payload starts after first word
    for (i = 4; i < nargs + 4 && i < sizeof(mbox->data.bytes); ++i)
        mbox->data.bytes[i] = va_arg(va, int); // need to cast to int...
    return mboxtester_write_ack(mbox);
}

ssize_t mbox_request(uint8_t cmd, unsigned nargs, ...)
{
    va_list va;
    va_start(va, nargs);
    ssize_t rc = mbox_request_va(&mbox_out, cmd, nargs, va);
    va_end(va);
    return rc;
}

ssize_t mbox_rpc(uint8_t cmd, unsigned nargs, ...)
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

void mbox_open_or_die(struct mbox *mbox, const char* path, int notif_type,
		      int timeout_ms, int flags)
{
    int rc = mbox_open(mbox, path, flags);
    if (rc) {
        fprintf(stderr, "mbox_open: %s: %s\n", path, strerror(errno));
        exit(-rc);
    }
    mbox_set_notif_type(mbox, notif_type);
    mbox_set_timeout_ms(mbox, timeout_ms);
}
