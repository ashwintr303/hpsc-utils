# Paths to host tools and target binaries for run-qemu.sh.
# Relative paths are relative to directory from where run-qemu.sh is invoked.

if [ -z "$PROF" ]
then
    echo "ERROR: PROF must be set when sourcing the env" 1>&2
    exit 1
fi

SSW=$HPSC_ROOT/ssw
SDK=$HPSC_ROOT/sdk

# Revisit: needs to be split between SDK and SSW
HPSC_UTILS_DIR=$HPSC_ROOT/hpsc-utils

HPPS_DIR=$SSW/hpps
RTPS_DIR=$SSW/rtps
RTPS_R52_DIR=$RTPS_DIR/r52
RTPS_A53_DIR=$RTPS_DIR/a53

TOOLS=${HPSC_UTILS_DIR}/sdk/host
CONF_DIR=$HPSC_UTILS_DIR/conf/base
CONF_TRCH_DIR=${CONF_DIR}/trch

# artifacts produced by top-level build
BLD=$SSW/bld

SDK_BLD=$SDK/bld
PROFS_DIR=$BLD/prof
PROF_DIR=$PROFS_DIR/$PROF

PROF_QEMU=$PROF_DIR/qemu
QEMU_DIR=$SDK_BLD/qemu
QEMU_BIN_DIR=$QEMU_DIR/aarch64-softmmu
QEMU_DT_FILE=${PROF_QEMU}/prof.qemu.dtb
QEMU_PREFIX=/usr/local

PROF_TRCH=$PROF_DIR/trch
TRCH_SMC_SRAM=${PROF_TRCH}/prof.sram.mem.bin

MEMORY_FILE=$PROF_QEMU/prof.preload.mem.map
