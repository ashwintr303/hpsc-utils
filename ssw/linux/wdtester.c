#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static volatile int running = 1;

static void shandle(int sig) {
  switch (sig) {
    case SIGTERM:
    case SIGINT:
      running = 0;
    default:
      break;
  }
}

int main(int argc, char** argv) {
    int fd;
    int do_write;
    const char* fname;
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <device_file> <do_writes>\n", argv[0]);
        return EINVAL;
    }
    fname = argv[1];
    do_write = atoi(argv[2]);
    signal(SIGINT, shandle);
    if ((fd = open(fname, O_WRONLY | O_CLOEXEC)) < 0) {
        perror(fname);
        return errno;
    }
    while (running) {
        if (do_write) {
            printf("Kicking watchdog: yes\n");
            if (write(fd, "\0", 1) < 0) {
                perror("write");
            }
        } else {
            printf("Kicking watchdog: no\n");
        }
        sleep(1);
    }
    printf("Stopping\n");
    if (write(fd, "V", 1) < 0) {
        perror("write: failed to stop");
        return errno;
    }
    if (close(fd) == -1) {
        perror("close");
        return errno;
    }
    return 0;
}
