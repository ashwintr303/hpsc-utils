// From TRCH/RTPS command.h
#define CMD_NOP                         0
#define CMD_PING                        1
#define CMD_PONG                        2
#define CMD_MBOX_LINK_CONNECT           200
#define CMD_MBOX_LINK_DISCONNECT        201
#define CMD_MBOX_LINK_PING              202

#define ENDPOINT_HPPS 0
#define ENDPOINT_RTPS 1

struct mbox mbox_out;
struct mbox mbox_in;

const char *expand_path(const char *path, char *buf, size_t size);

const char *cmd_to_str(uint8_t cmd);

ssize_t mboxtester_write_ack(struct mbox *mbox);

ssize_t mboxtester_read(struct mbox *mbox);

ssize_t mbox_request(uint8_t cmd, unsigned nargs, ...);

ssize_t mbox_rpc(uint8_t cmd, unsigned nargs, ...);

void mbox_open_or_die(struct mbox *mbox, const char* path,
		      int notif_type, int timeout_ms, int flags);
