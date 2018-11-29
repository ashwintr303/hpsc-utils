#!/bin/bash

# Note: Before running the following script, please make sure to:
#
# 1.  Run the "build-hpsc-yocto.sh" script with the "bitbake core-image-minimal"
#     option in order to generate many of the needed QEMU files.
#
# 2.  Run the "build-hpsc-baremetal.sh" script (with the proper toolchain
#     path) to create the baremetal firmware files "trch.elf" and "rtps.elf".
#
# 3.  Update the MY_IP_ADDR variable below.

# The following variable needs to be updated:
MY_IP_ADDR=192.168.122.1

# Output files from the Yocto build
YOCTO_DEPLOY_DIR=${PWD}/poky/build/tmp/deploy/images/hpsc-chiplet
YOCTO_QEMU_DIR=${PWD}/poky/build/tmp/work/x86_64-linux/qemu-native/2.11.1-r0/image/usr/local/bin
ARM_TF_FILE=${YOCTO_DEPLOY_DIR}/arm-trusted-firmware.elf # TODO: consider renaming this to bl31.elf or atf-bl31.elf to show that we're only using stage 3.1
ROOTFS_FILE=${YOCTO_DEPLOY_DIR}/core-image-minimal-hpsc-chiplet.cpio.gz.u-boot
KERNEL_FILE=${YOCTO_DEPLOY_DIR}/Image
LINUX_DT_FILE=${YOCTO_DEPLOY_DIR}/hpsc.dtb
QEMU_DT_FILE=${YOCTO_DEPLOY_DIR}/qemu-hw-devicetrees/hpsc-arch.dtb
BL_FILE=${YOCTO_DEPLOY_DIR}/u-boot.elf

# Output files from the hpsc-baremetal build
BAREMETAL_DIR=${PWD}/hpsc-baremetal
TRCH_FILE=${BAREMETAL_DIR}/trch/bld/trch.elf
RTPS_FILE=${BAREMETAL_DIR}/rtps/bld/rtps.elf

# External storage (NAND, SRAM) devices
# how to use:
#	-drive file=$HPPS_NAND_IMAGE,if=pflash,format=raw,index=3 \
#	-drive file=$HPPS_SRAM_FILE,if=pflash,format=raw,index=2 \
#	-drive file=$TRCH_SRAM_FILE,if=pflash,format=raw,index=0 \

HPPS_NAND_IMAGE=${YOCTO_DEPLOY_DIR}/rootfs_nand.bin
HPPS_SRAM_FILE=${YOCTO_DEPLOY_DIR}/hpps_sram.bin
TRCH_SRAM_FILE=${YOCTO_DEPLOY_DIR}/trch_sram.bin

# Controlling boot mode of HPPS (ramdisk or rootfs in NAND)
# how to use:
#	-device loader,addr=$BOOT_MODE_ADDR,data=$BOOT_MODE,data-len=4,cpu-num=3 \

BOOT_MODE_ADDR=0x80000000	# memory location to store boot mode code for U-boot
BOOT_MODE=0x00000000	# rootfs in RAM
#BOOT_MODE=0x0000f000	# rootfs in NAND (MTD device)

# See QEMU User Guide in HPSC release for explanation of the command line arguments
# NOTE: order of -device args may matter, must load ATF last, because loader also sets PC
KERNEL_ADDR=0x80080000
LINUX_DT_ADDR=0x84000000
ROOTFS_ADDR=0x90000000

# Note: If you want to see instructions at a large performance cost, then add "in_asm" into
# the following command as such: "-D /tmp/qemu.log -d fdt,guest_errors,unimp,cpu_reset,in_asm \"
#gdb --args \
${YOCTO_QEMU_DIR}/qemu-system-aarch64 \
	-machine arm-generic-fdt \
	-serial udp:${MY_IP_ADDR}:4441@:4451 \
	-serial udp:${MY_IP_ADDR}:4442@:4452 \
	-serial udp:${MY_IP_ADDR}:4443@:4453 \
	-nographic \
	-s -D /tmp/qemu.log -d fdt,guest_errors,unimp,cpu_reset \
	-hw-dtb ${QEMU_DT_FILE} \
	-device loader,addr=${ROOTFS_ADDR},file=${ROOTFS_FILE},force-raw,cpu-num=3 \
	-device loader,addr=${LINUX_DT_ADDR},file=${LINUX_DT_FILE},force-raw,cpu-num=3 \
	-device loader,addr=${KERNEL_ADDR},file=${KERNEL_FILE},force-raw,cpu-num=3 \
	-device loader,file=${BL_FILE},cpu-num=3 \
	-device loader,file=${ARM_TF_FILE},cpu-num=3 \
	-device loader,file=${RTPS_FILE},cpu-num=2 \
	-device loader,file=${RTPS_FILE},cpu-num=1 \
	-device loader,file=${TRCH_FILE},cpu-num=0  \
        -net nic,vlan=0 -net user,vlan=0,hostfwd=tcp:127.0.0.1:2345-10.0.2.15:2345,hostfwd=tcp:127.0.0.1:10022-10.0.2.15:22 \
