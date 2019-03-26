## Prepare

The following instructions assume that the root of the source tree has a
symbolic link named `Makefile` that points to the top-level makefile
in this repository. If the link does not exist, created it with:

    $ ln -sf hpsc-utils/make/Makefile.hpsc Makefile


The build requires that the toolchains referenced in Makefile under `CROSS_*`
variables are reachable via PATH:

    $ export PATH=$PATH:/opt/gcc-arm-none-eabi-7-2018-q2-update/bin
    $ export PATH=$PATH:/opt/gcc-linaro-7.4.1-2019.02-x86_64_aarch64-linux-gnu/bin

Toolchains tested:

* aarch64-linux-gnu-: [gcc-linaro-7.4.1-2019.02-x86_64_aarch64-linux-gnu.tar.xz from Linaro][1]
* arm-none-eabi- [for M4 and R52 bare metal): [gcc-arm-none-eabi-7-2018-q2--linux.tar.bz2][2]

[1] https://releases.linaro.org/components/toolchain/binaries/latest-7/aarch64-linux-gnu/gcc-linaro-7.4.1-2019.02-x86_64_aarch64-linux-gnu.tar.xz

[2] https://developer.arm.com/-/media/Files/downloads/gnu-rm/7-2018q2/gcc-arm-none-eabi-7-2018-q2-update-linux.tar.bz2?revision=bc2c96c0-14b5-4bb4-9f18-bceb4050fee7?product=GNU%20Arm%20Embedded%20Toolchain,64-bit,,Linux,7-2018-q2-update

Other toolchain distributables may work as well, with the known exceptions:
* GCC v8 breaks build of kernel 4.14 (build completes but kernel does not run)
* gcc-arm-none-eabi v8 (from ARM, not Linaro) breaks build of M4,R52 bare metal
* gcc-arm-none-eabi older than v7 2018-q2-update breaks build of R52 bare metal

## Build

To build all host tools, Qemu emulator, and target code:

    $ make

Each component as well as groups of related components can be built separate
via an (phony) target, for example, `hpps`, `hpps-linux`, etc, like so

    $ make hpps

The phony targets trigger a deep build, i.e. they invoke the nested
dependency builds.

Non-phony targets exist for top-level artifacts (real files), e.g.
the bootloader image `hpps/u-boot/u-boot.bin`. These targets trigger
a shallow build, i.e. they do but invoke the nested dependency build
unless the target file does not exist at all.

## Running Qemu

Set `$HPSC_ROOT` to the absolute path of the source tree:

    $ export HPSC_ROOT=/path/to/hpsc

Add the location of host tools to PATH for convenience:

    $ export PATH=$PATH:$HPSC_ROOT/hpsc-utils/host


Create a directory which will store artifacts associated with a Qemu run,
and launch Qemu from this directory. Preferably place the run directory outside
of this source tree, since it would be picked up as untracked by git status,

    $ mkdir ~/qemu-run
    $ cd ~/qemu-run
    $ run-qemu.sh

Several alternative run configurations (e.g. uncopressed kernel, etc) are
available as "profiles" in `hpsc-utils/conf/prof`. To select a profile:

    $ run-qemu.sh -p profile-name

The default configuration for Qemu invocation is defined in
`hpsc-utils/conf/base/qemu/qemu-env.sh`. Each profile may override this
configuration in a file with the same name in the profile subdirectory.

Configuration may be overriden further by creating a `qemu-env.sh`
file in the current working directory from where `run-qemu.sh` is invoked.

To temporarily add arguments to QEMU command line (for example, to enable
trace), add them as a Bash array to QEMU\_ARGS either in `qemu-env.sh` or as an
environment variable:

    $ export QEMU_ARGS=(-etrace-flags mem -etrace /tmp/trace)

### Multiuser setup with a shared source tree

Multiple users may run Qemu using one source tree, without write access to that
source tree directory. The shared copy would contain built artifacts. If a user
wishes to modify some code, the user may create a copy of the respective
sub-folder anywhere, and point Qemu to the binaries produced in the local copy
via `qemu-env.sh` as described above.

For example, to modify ATF (while re-using everything else), first copy
it from the parent repo (or alternatively clone the respective git repository):

    $ mkdir -p hpsc-sw/hpps
    $ cp -r $HPSC_ROOT/hpps/arm-trusted-firmware ~/hpsc-sw/hpps/

Then, override the path to the target binary by adding to `~/qemu-run/qemu-env.sh`:

    HPPS_FW=~/hpsc-sw/hpps/arm-trusted-firmware/build/hpsc/debug/bl31.bin

For the variable name and for the path of each target artifact relative to the
respective source tree, see the base env config `qemu-env.sh` mentioned above.
