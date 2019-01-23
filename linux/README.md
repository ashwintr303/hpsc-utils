HPSC Linux Utilities
====================

This directory contains test utilities to be run in Linux on the HPPS subsystem.
To push files to HPPS running in Qemu, use scp:

    scp -P 10022 [FILE]... root@127.0.0.1:

e.g., 

    scp -P 10022 mboxtester rtit-tester shmtester wdtester root@127.0.0.1:

By default, the files will be in `/home/root/` on HPPS.

Build
-----

First, you must source the poky cross-toolchain environment setup script, then
unset the `LDFLAGS` environment variable, e.g.:

    . /opt/poky/2.6/environment-setup-aarch64-poky-linux
    unset LDFLAGS

Then you may build:

    make

You should see output like:

```sh
aarch64-poky-linux-gcc  --sysroot=/opt/poky/2.6/sysroots/aarch64-poky-linux  -O2 -pipe -g -feliminate-unused-debug-types  -O1 -g -o mboxtester mboxtester.c
aarch64-poky-linux-gcc  --sysroot=/opt/poky/2.6/sysroots/aarch64-poky-linux  -O2 -pipe -g -feliminate-unused-debug-types  -O1 -g -o shmtester shmtester.c
aarch64-poky-linux-gcc  --sysroot=/opt/poky/2.6/sysroots/aarch64-poky-linux  -O2 -pipe -g -feliminate-unused-debug-types  -O1 -g -o wdtester wdtester.c
aarch64-poky-linux-gcc  --sysroot=/opt/poky/2.6/sysroots/aarch64-poky-linux  -O2 -pipe -g -feliminate-unused-debug-types  -O1 -g -o rtit-tester rtit-tester.c
```

If instead you see output like the following, the cross-compiler wasn't used:

```sh
cc -O1 -g -o mboxtester mboxtester.c
cc -O1 -g -o shmtester shmtester.c
cc -O1 -g -o wdtester wdtester.c
cc -O1 -g -o rtit-tester rtit-tester.c
```

For additional details, see:
https://www.yoctoproject.org/docs/2.6/sdk-manual/sdk-manual.html#makefile-based-projects

mboxtester
----------

HPSC Mailbox Tester is a Linux application for sending a message and reading a
reply from a mailbox, either TRCH or RTPS. The tester follows a simple protocol
for request and reply messages, which is also followed by a command server
that processes requests on TRCH and/or RTPS.

The tester writes a request to the output mailbox and reads a reply from
the input mailbox. The usage is:

    ./mboxtester [out_mbox_path|filename|index in_mbox_path|filename|index  [mbox_own_out mbox_own_in]]

The input and output mailboxes can be specified by either the full path to the
device file, e.g. `/dev/mbox/0/mbox0` or as an index which will
be expanded into a path, e.g. `0` will expand into the above path.

If no arguments are specified, the following default is assumed: `./mboxtester 0 1`.

shmtester
---------

The shared memory tester reads and writes to shared memory regions specified in
the device tree.

For example, to read 32 bytes for `region0`:

	./shmtester -f /dev/hpsc_shmem/region0 -l 32 -r

or to read and write `0xff` to the 32 bytes:

	./shmtester -f /dev/hpsc_shmem/region0 -l 32 -r -w 0xff

The data is verified after writing by re-reading the the specified length.
Other test options include checking for prior values in the region and working
at a page offset within the region.
Use the `-h` option for further details.

wdtester
--------

This tester kicks watchdog devices at regular intervals.
Usage:

    ./wdtester <device_file> <do_writes>

where `device_file` is the path to a watchdog dev file, e.g., `/dev/watchdog3`
and `do_writes` is a boolean value for whether it will actually kick (1) or not
(0).
Failure to kick a mailbox will result in the watchdog timing out.
The `wdtester` should also be fixed to the core that it's kicking, e.g.:

    taskset -c 3 ./wdtester /dev/watchdog3 1

Note that HPSC watchdogs cannot be stopped once they are started, but the SW
watchdog can.
See `/sys/class/watchdog/watchdog[N]/identity` to check type for watchdog `[N]`.
