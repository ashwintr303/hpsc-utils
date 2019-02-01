#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#define CMD_PING 1
#define CMD_PONG 2

// All subsystems must understand this structure and its protocol
// size aligns with mailbox messages
#define SHMEM_MSG_SIZE 64
struct hpsc_shmem_region {
    uint8_t data[SHMEM_MSG_SIZE];
    uint32_t is_new;
};
#define SHM_SIZE sizeof(struct hpsc_shmem_region)

struct shm_conn {
    const char *file;
    int fd;
    void *reg;
    volatile struct hpsc_shmem_region *shm;
};

#define IFILE_DEFAULT "/dev/hpsc_shmem/region0"
#define OFILE_DEFAULT "/dev/hpsc_shmem/region1"

#define OPEN_FLAGS (O_RDWR | O_SYNC)
#define MMAP_FLAGS (MAP_SHARED | MAP_NORESERVE)
#define MMAP_PROT (PROT_READ | PROT_WRITE)

static int shm_conn_open(struct shm_conn *conn)
{
    conn->fd = open(conn->file, OPEN_FLAGS);
    if (conn->fd < 0) {
        fprintf(stderr, "open: %s: %s\n", conn->file, strerror(errno));
        return errno;
    }
    conn->reg = mmap(NULL, SHM_SIZE, MMAP_PROT, MMAP_FLAGS, conn->fd, 0);
    if (conn->reg == MAP_FAILED) {
        fprintf(stderr, "mmap: %s: %s\n", conn->file, strerror(errno));
        return errno;
    }
    conn->shm = (volatile struct hpsc_shmem_region *) conn->reg;
    return 0;
}

static int shm_conn_close(struct shm_conn *conn)
{
    int rc = 0;
    if (munmap(conn->reg, SHM_SIZE)) {
        fprintf(stderr, "munmap: %s: %s\n", conn->file, strerror(errno));
        rc = errno;
    }
    if (close(conn->fd)) {
        fprintf(stderr, "close: %s: %s\n", conn->file, strerror(errno));
        rc = errno;
    }
    return rc;
}

static void usage(const char *pname, int code)
{
    fprintf(code ? stderr : stdout,
            "Usage: %s [-i FILE] [-o FILE] [-h]\n"
            "  -i, --in=FILE        The inbound shared memory device file to use\n"
            "                       default = "IFILE_DEFAULT"\n"
            "  -o, --out=FILE       The outbound shared memory device file to use\n"
            "                       default = "OFILE_DEFAULT"\n"
            "  -h, --help           Print this message and exit\n",
            pname);
    exit(code);
}

static const char short_options[] = "i:o:h";
static const struct option long_options[] = {
    {"in",      required_argument,  NULL,   'i'},
    {"out",     required_argument,  NULL,   'o'},
    {"help",    no_argument,        NULL,   'h'},
    {0, 0, 0, 0}
};

int main(int argc, char **argv)
{
    struct shm_conn iconn = { .file = IFILE_DEFAULT };
    struct shm_conn oconn = { .file = OFILE_DEFAULT };
    int c;
    int ret;

    // parse options
    while ((c = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {
        switch (c) {
        case 'i':
            iconn.file = optarg;
            break;
        case 'o':
            oconn.file = optarg;
            break;
        case 'h':
            usage(argv[0], 0);
            break;
        default:
            usage(argv[0], EINVAL);
            break;
        }
    }

    // open connections
    ret = shm_conn_open(&iconn) || shm_conn_open(&oconn);
    if (ret) {
        return ret;
    }

    // clear the outbound region
    memset(oconn.reg, 0, SHM_SIZE);
    // clearing inbound status allows remote to always send reply
    iconn.shm->is_new = 0;

    // write to remote
    oconn.shm->data[0] = CMD_PING;
    oconn.shm->data[4] = 0xFF;
    oconn.shm->is_new = 1;

    // wait for remote to ACK and reply
    printf("Wrote PING, waiting for ACK...\n");
    while (oconn.shm->is_new);
    printf("Got ACK, waiting for PONG...\n");
    while (!iconn.shm->is_new);

    // read reply
    if (iconn.shm->data[0] == CMD_PONG) {
        printf("Got PONG\n");
        iconn.shm->is_new = 0;
    } else {
        fprintf(stderr, "Got unexpected response: %"PRIu32"\n",
                iconn.shm->data[0]);
        ret |= EAGAIN;
    }

    // clean up
    ret |= shm_conn_close(&oconn);
    ret |= shm_conn_close(&iconn);
    return ret;
}
