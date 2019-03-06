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

static void print_region(const char *msg, volatile void *reg, size_t s)
{
    size_t i;
    printf("%s", msg);
    for (i = 0; i < s; i++) {
        printf(" 0x%02x", ((unsigned char *)reg)[i]);
    }
    printf("\n");
}

static int verify_region(volatile void *reg, int c, size_t s)
{
    size_t i;
    for (i = 0; i < s; i++) {
        if (((unsigned char *)reg)[i] != c) {
            return -1;
        }
    }
    return 0;
}

static int execute_test(const char *file, size_t size, int is_write, int write,
                        off_t off, int has_prior, int prior, int is_read)
{
    int ret;
    int o_flags;
    int prot = PROT_NONE;
    int fd;
    // Technically doesn't need to be volatile since this is a standalone test,
    // but real code that wants to share memory with other subsystems must be.
    volatile void *reg;

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
    reg = mmap(NULL, size, prot, FLAGS, fd, off);
    if (reg == MAP_FAILED) {
        perror("mmap");
        if (errno == EINVAL) {
            fprintf(stderr, "Hint: is size or offset too large?\n");
        }
        return errno;
    }

    // pre-write work
    if (is_read) {
        print_region("Start:", reg, size);
    }
    if (has_prior && verify_region(reg, prior, size)) {
        fprintf(stderr, "prior: validation failed!\n");
        return EFAULT;
    }

    // Write memory
    if (is_write) {
        // memset - writes don't need to be volatile, we opened with O_SYNC
        memset((void *)reg, write, size);
        // post-write work
        if (is_read) {
            print_region("End:", reg, size);
        }
        if (verify_region(reg, write, size)) {
            fprintf(stderr, "write: validation failed!\n");
            return EFAULT;
        }
    }

    // clean up
    ret = munmap((void *)reg, size);
    if (ret) {
        perror("munmap");
    }
    ret = close(fd);
    if (ret) {
        perror("close");
    }
    return ret;
}

static void usage(const char *pname, int code)
{
    fprintf(code ? stderr : stdout,
            "Usage: %s -f FILE -s SIZE [-w BYTE] [-o OFF] [-p BYTE] [-r] [-l N] [-h]\n"
            "  -f, --file=FILE      The shared memory device file to use\n"
            "  -s, --size=SIZE      The size in bytes (SIZE > 0) to read/write\n"
            "  -w, --write=BYTE     The byte value to write to memory\n"
            "  -o, --offset=OFF     The offset in pages (OFF >= 0) to mmap (default=0)\n"
            "                       For page size, see sysconf(_SC_PAGE_SIZE)\n"
            "  -p, --prior=BYTE     The expected byte value prior to writing\n"
            "  -r, --read           Read memory before and/or after optional write\n"
            "  -l, --loop=N         Run the test N times (default = 1)\n"
            "  -h, --help           Print this message and exit\n",
            pname);
    exit(code);
}

static const char short_options[] = "f:s:w:o:p:rl:h";
static const struct option long_options[] = {
    {"file",    required_argument,  NULL,   'f'},
    {"size",    required_argument,  NULL,   's'},
    {"write",   required_argument,  NULL,   'w'},
    {"offset",  required_argument,  NULL,   'o'},
    {"prior",   required_argument,  NULL,   'p'},
    {"read",    no_argument,        NULL,   'r'},
    {"loop",    required_argument,  NULL,   'l'},
    {"help",    no_argument,        NULL,   'h'},
    {0, 0, 0, 0}
};

int main(int argc, char **argv)
{
    int c;
    const char *file = NULL;
    size_t size = 0;
    int is_write = 0;
    int write = 0;
    off_t off = 0;
    int has_prior = 0;
    int prior = 0;
    int is_read = 0;
    unsigned long loop = 1;
    unsigned long i;
    int ret = 0;

    // parse options
    while ((c = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {
        switch (c) {
        case 'f':
            file = optarg;
            break;
        case 's':
            errno = 0;
            size = strtoull(optarg, NULL, 0);
            if (size == ULLONG_MAX && errno) {
                perror("strtoull: size");
                usage(argv[0], errno);
            }
            break;
        case 'w':
            write = strtoul(optarg, NULL, 0);
            is_write = 1;
            break;
        case 'o':
            errno = 0;
            off = strtoll(optarg, NULL, 0);
            if ((off == LLONG_MIN || off == LLONG_MAX) && errno) {
                perror("strtoull: offset");
                usage(argv[0], errno);
            }
            if (off < 0) {
                fprintf(stderr, "offset must be >= 0\n");
                usage(argv[0], EINVAL);
            }
            break;
        case 'p':
            prior = strtoul(optarg, NULL, 0);
            has_prior = 1;
            break;
        case 'r':
            is_read = 1;
            break;
        case 'l':
            loop = strtoul(optarg, NULL, 0);
            break;
        case 'h':
            usage(argv[0], 0);
            break;
        default:
            usage(argv[0], EINVAL);
            break;
        }
    }
    if (file == NULL || size == 0) {
        usage(argv[0], EINVAL);
    }

    for (i = 0; i < loop; i++) {
        printf("Test iteration: %lu\n", i + 1);
        ret = execute_test(file, size, is_write, write,
                           off, has_prior, prior, is_read);
        if (ret) {
            break;
        }
    }

    return ret;
}
