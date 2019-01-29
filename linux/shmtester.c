#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#define FLAGS (MAP_SHARED | MAP_NORESERVE)

static void print_region(const char *msg, void *reg, size_t s)
{
    size_t i;
    puts(msg);
    for (i = 0; i < s; i++) {
        printf(" 0x%02x", ((unsigned char *)reg)[i]);
    }
    printf("\n");
}

static int verify_region(void *reg, int c, size_t s)
{
    // TODO: could memcmp at word or page size if length is large enough
    size_t i;
    for (i = 0; i < s; i++) {
        if (((unsigned char *)reg)[i] != c) {
            return -1;
        }
    }
    return 0;
}

static void usage(const char *pname, int code)
{
    fprintf(code ? stderr : stdout,
            "Usage: %s -f FILE -l LEN [-w BYTE] [-o OFF] [-p BYTE] [-r] [-h]\n"
            "  -f, --file=FILE      The shared memory device file to use\n"
            "  -l, --length=LEN     The length in bytes (LEN > 0) to read/write\n"
            "  -w, --write=BYTE     The byte value to write to memory\n"
            "  -o, --offset=OFF     The offset (in pages) to mmap (default=0)\n"
            "                       For page size, see sysconf(_SC_PAGE_SIZE)\n"
            "  -p, --prior=BYTE     The expected byte value prior to writing\n"
            "  -r, --read           Read memory before and/or after optional write\n"
            "  -h, --help           Print this message and exit\n",
            pname);
    exit(code);
}

static const char short_options[] = "f:l:w:o:p:rh";
static const struct option long_options[] = {
    {"file",    required_argument,  NULL,   'f'},
    {"length",  required_argument,  NULL,   'l'},
    {"write",   required_argument,  NULL,   'w'},
    {"offset",  required_argument,  NULL,   'o'},
    {"prior",   required_argument,  NULL,   'p'},
    {"read",    no_argument,        NULL,   'r'},
    {"help",    no_argument,        NULL,   'h'},
    {0, 0, 0, 0}
};

int main(int argc, char **argv)
{
    int c;
    const char *file = NULL;
    size_t len = 0;
    int is_write = 0;
    int write = 0;
    off_t off = 0;
    int has_prior = 0;
    int prior = 0;
    int is_read = 0;
    int o_flags;
    int prot = PROT_NONE;
    int fd;
    void *reg;
    int ret;

    /// parse options
    while ((c = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {
        switch (c) {
        case 'f':
            file = optarg;
            break;
        case 'l':
            len = strtoull(optarg, NULL, 0);
            if (len == ULLONG_MAX && errno) {
                perror("strtoull: length");
                usage(argv[0], errno);
            }
            break;
        case 'w':
            write = strtoul(optarg, NULL, 0);
            is_write = 1;
            break;
        case 'o':
            off = strtoull(optarg, NULL, 0);
            if (off == ULLONG_MAX && errno) {
                perror("strtoull: offset");
                usage(argv[0], errno);
            }
            break;
        case 'p':
            prior = strtoul(optarg, NULL, 0);
            has_prior = 1;
            break;
        case 'r':
            is_read = 1;
            break;
        case 'h':
            usage(argv[0], 0);
            break;
        default:
            usage(argv[0], EINVAL);
            break;
        }
    }
    if (file == NULL || len == 0) {
        usage(argv[0], EINVAL);
    }

    // open the shared memory device file, always use sync
    // mmap doesn't work with O_WRONLY, it must always have read permission
    o_flags = (is_write ? O_RDWR : O_RDONLY) | O_SYNC;
    fd = open(file, o_flags);
    if (fd < 0) {
        perror(file);
        return errno;
    }

    // mmap the device file
    if (is_read || has_prior) {
        prot |= PROT_READ;
    }
    if (is_write) {
        prot |= PROT_WRITE;
    }
    reg = mmap(NULL, len, prot, FLAGS, fd, off);
    if (reg == MAP_FAILED) {
        perror("mmap");
        if (errno == EINVAL) {
            fprintf(stderr, "Hint: is length or offset too large?\n");
        }
        return errno;
    }

    // pre-write work
    if (is_read) {
        print_region("Start:", reg, len);
    }
    if (has_prior && verify_region(reg, prior, len)) {
        fprintf(stderr, "prior: validation failed!\n");
        return EFAULT;
    }

    // Write memory
    if (is_write) {
        memset(reg, write, len);
        // post-write work
        if (is_read) {
            print_region("End:", reg, len);
        }
        if (verify_region(reg, write, len)) {
            fprintf(stderr, "write: validation failed!\n");
            return EFAULT;
        }
    }

    // clean up - done manually for testing purposes
    ret = munmap(reg, len);
    if (ret) {
        perror("munmap");
    }
    ret = close(fd);
    if (ret) {
        perror("close");
    }
    return ret;
}