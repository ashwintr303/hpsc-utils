# Paths to host tools and target binaries for run-qemu.sh.
# Relative paths are relative to directory from where run-qemu.sh is invoked.

HPPS_DIR=$HPSC_ROOT/hpps
RTPS_DIR=$HPSC_ROOT/rtps
RTPS_R52_DIR=$RTPS_DIR/r52
RTPS_A53_DIR=$RTPS_DIR/a53

HPSC_UTILS_DIR=$HPSC_ROOT/hpsc-utils
HPSC_HOST_UTILS_DIR=$HPSC_UTILS_DIR/host
CONF_DIR=$HPSC_UTILS_DIR/conf/base
CONF_TRCH_DIR=${CONF_DIR}/trch

SRAM_IMAGE_UTILS=${HPSC_HOST_UTILS_DIR}/sram-image-utils
NAND_CREATOR=${HPSC_HOST_UTILS_DIR}/qemu-nand-creator

# artifacts produced by top-level build
BIN=$HPSC_ROOT/bin
PROF_DIR=$BIN/prof

# HPPS artifacts
HPPS_BIN=$BIN/hpps
HPPS_FW=$HPPS_DIR/arm-trusted-firmware/build/hpsc/debug/bl31.bin
HPPS_BL=$HPPS_DIR/u-boot/u-boot.bin
HPPS_KERNEL_DIR=$HPPS_DIR/linux/arch/arm64/boot
HPPS_DT=$HPPS_KERNEL_DIR/dts/hpsc/hpsc.dtb
HPPS_KERN=$HPPS_BIN/uImage

# Output files from the hpsc-baremetal build
BAREMETAL_DIR=$HPSC_ROOT/hpsc-baremetal
TRCH_APP=${BAREMETAL_DIR}/trch/bld/trch.elf
RTPS_APP=${BAREMETAL_DIR}/rtps/bld/rtps.uimg

# Output files from the hpsc-R52-uboot build
RTPS_BL_DIR=$RTPS_R52_DIR/u-boot
RTPS_BL=${RTPS_BL_DIR}/u-boot.bin

# Output files from the qemu/qemu-devicetree builds
QEMU_DIR=$BIN/qemu-bld
QEMU_BIN_DIR=$QEMU_DIR/aarch64-softmmu
QEMU_DT_FILE=$HPSC_ROOT/qemu-devicetrees/LATEST/SINGLE_ARCH/hpsc-arch.dtb

# System configuration interpreted by TRCH
SYSCFG=${CONF_TRCH_DIR}/syscfg.ini
SYSCFG_SCHEMA=${CONF_TRCH_DIR}/syscfg-schema.json