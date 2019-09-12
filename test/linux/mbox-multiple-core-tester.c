#define _GNU_SOURCE

#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <sched.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mailbox-map.h"
#include "libmbox/mbox.h"

#include "mbox-utils.h"

#define PATH_SIZE 128
#define MAX_HPPS_CPU_NUM 7

enum mbox_notif notif_type = MBOX_NOTIF_NONE;
int timeout_ms = -1;

// these align with enum mbox_notif
const char* const NOTIF_TYPE_NAMES[] = {
    "none",
    "select",
    "poll",
    "epoll"
};

static int execute_test(const char *devpath_out, const char *devpath_in,
			int cpu1, int cpu2)
{
    ssize_t rc_req;
    int rc = 0;

    // first pin to core cpu1
    cpu_set_t cpumask;
    CPU_ZERO(&cpumask);
    CPU_SET(cpu1, &cpumask);
    sched_setaffinity(0, sizeof(cpu_set_t), &cpumask);

    mbox_open_or_die(&mbox_out, devpath_out, notif_type, timeout_ms, O_RDWR); // read gets us the [N]ACK
    mbox_open_or_die(&mbox_in, devpath_in, notif_type, timeout_ms, O_RDONLY);

    printf("First perform PING-PONG using CPU %d\n", cpu1);
    rc_req = mbox_rpc(CMD_PING, 1, 42);
    if (rc_req < 0) {
        printf("In error1\n");
        perror("mbox_rpc: CMD_PING");
        rc = errno;
	goto cleanup;
    }

    // now pin to core cpu2
    CPU_ZERO(&cpumask);
    CPU_SET(cpu2, &cpumask);
    sched_setaffinity(0, sizeof(cpu_set_t), &cpumask);

    printf("Then use same mailboxes to perform PING-PONG using CPU %d\n", cpu2);
    rc_req = mbox_rpc(CMD_PING, 1, 42);
    if (rc_req < 0) {
        printf("In error2\n");
        perror("mbox_rpc: CMD_PING");
        rc = errno;
	goto cleanup;
    }

cleanup:
    mbox_close(&mbox_out);
    mbox_close(&mbox_in);
    return rc;
}

static void usage(const char *pname, int code)
{
    fprintf(code ? stderr : stdout,
            "Usage: %s [-o FILE] [-i FILE] [-n TYPE] [-t N] [-C CPU] [-c CPU] [-l N] [-h]\n"
            "  -o, --out=FILE       The outbound mailbox path, filename, or index\n"
            "                       The default value is 0, for /dev/mbox/0/mbox0\n"
            "  -i, --in=FILE        The inbound mailbox path, filename, or index\n"
            "                       The default value is 1, for /dev/mbox/0/mbox1\n"
            "  -n, --not-type=TYPE  Notification type, one of: none, select, poll, epoll\n"
            "                       The default value is \"none\"\n"
            "  -t, --timeout=N      Timeout for reads, in milliseconds\n"
            "                       The default value is -1 (infinite timeout)\n"
            "                       Specify a positive value, or 0 for no timeout\n"
            "  -C, --cpu1=CPU       First pin process to specified CPU\n"
            "                       The default value is 0\n"
            "  -c, --cpu2=CPU       Pin process to specified CPU after opening mailbox and pinging\n"
            "                       The default value is 1\n"
            "  -l, --loop=N         Run the test N times (default = 1)\n"
            "  -h, --help           Print this message and exit\n",
            pname);
    exit(code);
}

static const char short_options[] = "o:i:n:t:C:c:l:h";
static const struct option long_options[] = {
    {"out",         required_argument,  NULL,   'o'},
    {"in",          required_argument,  NULL,   'i'},
    {"not-type",    required_argument,  NULL,   'n'},
    {"timeout",     required_argument,  NULL,   't'},
    {"cpu1",        required_argument,  NULL,   'C'},
    {"cpu2",        required_argument,  NULL,   'c'},
    {"loop",        required_argument,  NULL,   'l'},
    {"help",        no_argument,        NULL,   'h'}
    //    {0, 0, 0, 0}
};

int main(int argc, char **argv) {
    char devpath_out_buf[PATH_SIZE];
    char devpath_in_buf[PATH_SIZE];
    const char *devpath_out = "0";
    const char *devpath_in = "1";
    int cpu1 = 0;
    int cpu2 = 1;
    unsigned long loop = 1;
    unsigned long i;
    int rc = 0;
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
        case 'C':
            cpu1 = atoi(optarg);
	    if ((cpu1 < 0) || (cpu1 > MAX_HPPS_CPU_NUM)) {
	        fprintf(stderr, "error: illegal value for CPU1\n");
		exit(1);
	    }
            break;
        case 'c':
            cpu2 = atoi(optarg);
	    if ((cpu2 < 0) || (cpu2 > MAX_HPPS_CPU_NUM)) {
	        fprintf(stderr, "error: illegal value for CPU2\n");
	        exit(2);
	    }
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

    printf("Config:\n");
    printf("  not-type:  %s\n", NOTIF_TYPE_NAMES[notif_type]);
    printf("  timeout:   %d\n", timeout_ms);
    printf("  cpu1:       %d\n", cpu1);
    printf("  cpu2:       %d\n", cpu2);

    devpath_out = expand_path(devpath_out, devpath_out_buf, sizeof(devpath_out_buf));
    devpath_in = expand_path(devpath_in, devpath_in_buf, sizeof(devpath_in_buf));
    if (!(devpath_out && devpath_in)) {
        fprintf(stderr, "error: failed to construct path\n");
        exit(3);
    }
    printf("  out:       %s\n", devpath_out);
    printf("  in:        %s\n", devpath_in);

    for (i = 0; i < loop; i++) {
        printf("\nTest iteration: %lu\n", i + 1);
        rc = execute_test(devpath_out, devpath_in, cpu1, cpu2);
        if (rc) {
            break;
        }
    }

    return rc;
}
