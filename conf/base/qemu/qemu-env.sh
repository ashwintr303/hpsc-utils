# Paths to host tools and target binaries for run-qemu.sh.
# Relative paths are relative to directory from where run-qemu.sh is invoked.

SSW=$HPSC_ROOT/ssw
SDK=$HPSC_ROOT/sdk

# Revisit: needs to be split between SDK and SSW
HPSC_UTILS_DIR=$HPSC_ROOT/hpsc-utils

HPPS_DIR=$SSW/hpps
RTPS_DIR=$SSW/rtps
RTPS_R52_DIR=$RTPS_DIR/r52
RTPS_A53_DIR=$RTPS_DIR/a53

HPSC_HOST_UTILS_DIR=$HPSC_UTILS_DIR/host
CONF_DIR=$HPSC_UTILS_DIR/conf/base
CONF_TRCH_DIR=${CONF_DIR}/trch

SRAM_IMAGE_UTILS=${HPSC_HOST_UTILS_DIR}/sram-image-utils
NAND_CREATOR=${HPSC_HOST_UTILS_DIR}/qemu-nand-creator

# artifacts produced by top-level build
BLD=$SSW/bld

SDK_BLD=$SDK/bld
PROF_DIR=$BLD/prof

# HPPS artifacts
HPPS_BLD=$BLD/hpps
HPPS_FW=$HPPS_DIR/arm-trusted-firmware/build/hpsc/debug/bl31.bin
HPPS_BL=$HPPS_DIR/u-boot/u-boot-nodtb.bin
HPPS_BL_DT=$HPPS_DIR/u-boot/u-boot.dtb
HPPS_BL_ENV=$HPPS_BLD/uboot.env.bin
HPPS_KERNEL_DIR=$HPPS_DIR/linux/arch/arm64/boot
HPPS_DT=$HPPS_KERNEL_DIR/dts/hpsc/hpsc.dtb
HPPS_KERN=$HPPS_BLD/uImage
HPPS_INITRAMFS=$HPPS_BLD/initramfs.uimg

# Output files from the hpsc-baremetal build
BAREMETAL_DIR=$SSW/hpsc-baremetal
TRCH_APP=${BAREMETAL_DIR}/trch/bld/trch.elf
RTPS_APP=${BAREMETAL_DIR}/rtps/bld/rtps.uimg

# Output files from the hpsc-R52-uboot build
RTPS_BL_DIR=$RTPS_R52_DIR/u-boot
RTPS_BL=${RTPS_BL_DIR}/u-boot.bin

# Output files from the qemu/qemu-devicetree builds
QEMU_DIR=$SDK_BLD/qemu
QEMU_BIN_DIR=$QEMU_DIR/aarch64-softmmu
QEMU_DT_FILE=$SDK/qemu-devicetrees/LATEST/SINGLE_ARCH/hpsc-arch.dtb

# System configuration interpreted by TRCH
SYSCFG=${CONF_TRCH_DIR}/syscfg.ini
SYSCFG_SCHEMA=${CONF_TRCH_DIR}/syscfg-schema.json
