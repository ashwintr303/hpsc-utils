# Paths to host tools and target binaries for run-qemu.sh.
# Relative paths are relative to directory from where run-qemu.sh is invoked.

if [ -z "$PROFILE" ]
then
    echo "ERROR: PROFILE must be set when sourcing the env" 1>&2
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
PROF_DIR=$BLD/prof
PROF=$PROF_DIR/$PROFILE

# HPPS artifacts
PROF_HPPS=$PROF/hpps
HPPS_BLD=$BLD/hpps
HPPS_FW=$HPPS_DIR/arm-trusted-firmware/build/hpsc/debug/bl31.bin
HPPS_BL=$HPPS_DIR/u-boot/u-boot-nodtb.bin
HPPS_BL_DT=$HPPS_DIR/u-boot/u-boot.dtb
HPPS_BL_ENV=$PROF_HPPS/prof.hpps-uboot.env.bin
HPPS_KERNEL_DIR=$HPPS_DIR/linux/arch/arm64/boot
HPPS_DT=$HPPS_KERNEL_DIR/dts/hpsc/hpsc.dtb
HPPS_KERN=$HPPS_BLD/uImage
HPPS_INITRAMFS=$PROF_HPPS/initramfs.uimg

# Output files from the hpsc-baremetal build
BAREMETAL_DIR=$SSW/hpsc-baremetal
TRCH_APP=${BAREMETAL_DIR}/trch/bld/trch.elf
RTPS_APP=${BAREMETAL_DIR}/rtps/bld/rtps.uimg

# Output files from the hpsc-R52-uboot build
RTPS_BL_DIR=$RTPS_R52_DIR/u-boot
RTPS_BL=${RTPS_BL_DIR}/u-boot.bin

# Output files from the qemu/qemu-devicetree builds
PROF_QEMU=$PROF/qemu
QEMU_DIR=$SDK_BLD/qemu
QEMU_BIN_DIR=$QEMU_DIR/aarch64-softmmu
QEMU_DT_FILE=${PROF_QEMU}/prof.qemu.dtb
QEMU_PREFIX=/usr/local

PROF_TRCH=$PROF/trch
SYSCFG=${PROF_TRCH}/prof.syscfg.ini
SYSCFG_BIN=${PROF_TRCH}/prof.syscfg.bin
TRCH_SMC_SRAM=${PROF_TRCH}/prof.sram.mem.bin
