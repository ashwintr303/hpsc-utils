# Paths to host tools and target binaries for run-qemu.sh.
# Relative paths are relative to directory from where run-qemu.sh is invoked.

KERNEL_PATH=$HPSC_ROOT/linux-hpsc/arch/arm64/boot

HPSC_UTILS_DIR=$HPSC_ROOT/hpsc-utils
HPSC_HOST_UTILS_DIR=$HPSC_UTILS_DIR/host
CONF_DIR=$HPSC_UTILS_DIR/conf

SRAM_IMAGE_UTILS=${HPSC_HOST_UTILS_DIR}/sram-image-utils
NAND_CREATOR=${HPSC_HOST_UTILS_DIR}/qemu-nand-creator

# HPPS artifacts
HPPS_BIN=$HPSC_ROOT/bin/hpps # artifacts produced by top-level build
HPPS_FW=$HPSC_ROOT/arm-trusted-firmware/build/hpsc/debug/bl31.bin
HPPS_BL=$HPSC_ROOT/u-boot-a53/u-boot.bin
HPPS_DT=$KERNEL_PATH/dts/hpsc/hpsc.dtb
HPPS_KERN=$HPPS_BIN/uImage
HPPS_RAMDISK=$HPSC_ROOT/hpsc-bsp/poky/build/tmp/deploy/images/zcu102-zynqmp/rootfs.cpio.gz.u-boot

# Output files from the hpsc-baremetal build
BAREMETAL_DIR=$HPSC_ROOT/hpsc-baremetal
TRCH_APP=${BAREMETAL_DIR}/trch/bld/trch.elf
RTPS_APP=${BAREMETAL_DIR}/rtps/bld/rtps.uimg

# Output files from the hpsc-R52-uboot build
RTPS_BL_DIR=$HPSC_ROOT/u-boot-r52
RTPS_BL=${RTPS_BL_DIR}/u-boot.bin

# Output files from the qemu/qemu-devicetree builds
QEMU_DIR=$HPSC_ROOT/qemu-bld
QEMU_BIN_DIR=$QEMU_DIR/aarch64-softmmu
QEMU_DT_FILE=$HPSC_ROOT/qemu-devicetrees/LATEST/SINGLE_ARCH/hpsc-arch.dtb

# System configuration interpreted by TRCH
SYSCFG=${CONF_DIR}/syscfg.ini
SYSCFG_SCHEMA=${CONF_DIR}/syscfg-schema.json
