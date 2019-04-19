## Prepare

### Make config

To ensure your builds always run in parallel on all processors (unless
explicitly overriden), add to `~/.bashrc`:

    alias make="make -j$(nproc)"

Replace `$(nproc)` with a number to use fewer processors than all.

And apply with:

    $ source ~/.bashrc

To override this default setting, in any build, simply pass a `-j` option,
which will be appended, and will take precedence.

### Dependencies

To build and run software for the target, you need the SDK for the HPSC
Chiplet. The HPSC SDK is obtained either:

1. from the distribution in pre-built binary form in a standalone, relocatable,
   distribution-agnostic installer, or
2. can be built from source in place (without packaging into an installer).

#### Install SDK from installer

For developing target software only, it is sufficient to install the SDK from
the installer. You can either get the install from the distribution channel, or
you can build the installer from source and then install it. The installer
bundles *all* its dependencies (in a complete sysroot) and does not rely on any
system libraries.

TODO: source the environment script provided by the installer

####  Build SDK in place

For developing tools that are part of the SDK, including the Qemu emulator, the
SDK components can be built and run from source in place, without an
installation step. The SDK components are built against dependencies installed
in the system (i.e. from the OS distribution's packages).

To prepare for the build, ensure that in your copy of the source tree, the
`sdk/` directory contains the following symlinks to the makefiles (that are
version controled in the `hpsc-utils` repo):

    $ ln -sf ../hpsc-utils/sdk/make/Makefile.sdk sdk/Makefile
    $ ln -sf ../../hpsc-utils/sdk/make/Makefile.sysroot sdk/sysroot/Makefile

To install the dependencies necessary to build and use the SDK in place, either:

1. If you have root priviledges to install or update the system and wish to do
   so (recommended), then run as root the following target replacing `DISTRO`
   with your distribution (supported distributions: `centos7`):

        # make sdk-deps-DISTRO

2. If you do not have ability to install or update software in the system,
   then you may use the following comman to fetch the sources of the
   dependencies from the Internet, build them from source and install them into
   a sysroot, all as an unprivileged user (takes on the order of 5 minutes with
   parallel make, see Make config section).:

        $ make sdk-deps-sysroot

    If the machine is offline without internet access, first fetch the
    source archives on a machine with internet acccess:

        $ make sdk-fetch sdk-sysroot-fetch

    Then, copy the folling directories to the same paths on the offline
    machine, and re-run the original make command above:

        sdk/sysroot/bld/fetch/
        sdk/bld/fetch/

    Should any components fail to build, navigate to the component's
    build directory under `sdk/sysroot/bld/work/`, resolve the issue and re-run
    the make command at the top level. The build commands for the components
    are in sdk/sysroot/Makefile.

To build the SDK

    $ make sdk

To use the built SDK when building the target code, source its environment script:

    $ source sdk/bld/env.sh

## Build target software

Whether you installed the HPSC SDK from the installer or have built it in place
from source, source the respective environment script of the SDK as described
at the end of the respective subsection in the previous chapter on SDK:

    $ source /path/to/sdk-environment-script

To build all target code:

    $ make ssw

Each component as well as groups of related components can be built separate
via an (phony) target, for example, `ss-hpps`, `ssw-hpps-linux`, etc, like so

    $ make ssw-hpps

Clean targets are analogous, the component name is suffix with `-clean`, like:

    $ make ssw-hpps-clean

The phony targets trigger a deep build, i.e. they invoke the nested
dependency builds.

Non-phony targets exist for top-level artifacts (real files), e.g.
the bootloader image `hpps/u-boot/u-boot.bin`. These targets trigger
a shallow build, i.e. they do but invoke the nested dependency build
unless the target file does not exist at all.

The clean targets clean deeply also, including removing generated config files.
For shallow clean and any other custom build commands, navigate to the
respective component subfolder and use its build system.


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
