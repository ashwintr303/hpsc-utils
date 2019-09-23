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

For users of the `vim` editor, to apply syntax highlighting to some of
the custom config files, add to your `~/.vimrc`:

    au BufRead,BufNewFile *.mem.map setfiletype sh

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

Change to the system software directory:

	$ cd ssw

To view available configuration profiles:

    $ make

Pick a desired profile from the list, say 'sys-preload-hpps-busybox' which
preloads binaries into DRAM (via HW emulator), boots TRCH into the SSW
bare-metal application, and lets TRCH boot HPPS into Busybox on Linux via Arm
Trusted Firware and U-boot bootloader.

To build the profile (note: after first build, paths will exist and
autocomplete on the target name will work):

	$ make prof/sys-preload-hpps-busybox

Clean a profile (invokes clean on nested builds too, cleans everything):

	$ make prof/sys-preload-hpps-busybox/clean

Clean artifacts outside nested source trees (does not invoke nested builds):

	$ make prof/sys-preload-hpps-busybox/bld/clean

Invoke incremental nested build on a particular module (invokes only the
nested build but not recipes that would be invoked by prof/PROFILE/bld):

    $ make prof/sys-preload-hpps-busybox/bld/hpps/linux

Clean a module (invoke the nested build: only cleans artifacts within the
module's nested source tree, does not clean what prof/PROFILE/bld/clean cleans):

    $ make prof/sys-preload-hpps-busybox/bld/hpps/linux/clean

Build a particular non-nested artifact -- artifacts within the nested builds
are not part of the top-level dependency tree so can't refer to them, but any
other artifact that's in the build directory can be rebuilt as you would expect
(to rebuild it, remove the file before invoking make):

	$ make prof/sys-preload-hpps-busybox/bld/trch/syscfg.bin

Privatize module source directories (make a copy) and build them within that
copy to keep the profile build fully isolated from other profiles (not usually
needed nor desired, because want to share the nested builds across profiles):

	$ make PRIV=1 prof/sys-preload-hpps-busybox

The clean targets clean deeply also, including removing generated config files.
For shallow clean and any other custom build commands, navigate to the
respective component subfolder and use its build system.

# Run the SSW profile on a target platform

Run the profile in the Qemu emulator:

	$ make prof/sys-preload-hpps-busybox/run/qemu

Run the selected profile in the Zebu emulator

	$ make prof/sys-preload-hpps-busybox/run/zebu

Clean platform-related (emulator) run state:

	$ make prof/sys-preload-hpps-busybox/run/qemu/clean
