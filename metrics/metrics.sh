#!/bin/bash

run() {
    echo $@
    "$@"
}

elf() {
    run size "$1"
}

bin() {
    run stat -c '%s' "$1"
}

elf hpsc-baremetal/trch/bld/trch.elf
bin hpsc-baremetal/trch/bld/trch.bin
elf hpsc-baremetal/rtps/bld/rtps.elf
bin hpsc-baremetal/rtps/bld/rtps.bin

elf u-boot-a53/u-boot
bin u-boot-a53/u-boot.bin
elf u-boot-r52/u-boot
bin u-boot-r52/u-boot.bin

elf arm-trusted-firmware/build/hpsc/release/bl31/bl31.elf
bin arm-trusted-firmware/build/hpsc/release/bl31.bin

elf linux-hpsc/vmlinux
bin linux-hpsc/arch/arm64/boot/Image.gz

bin linux-hpsc/arch/arm64/boot/dts/hpsc/hpsc.dtb
bin u-boot-a53/arch/arm/dts/hpsc-hpps.dtb
bin u-boot-r52/arch/arm/dts/hpsc-rtps-r52.dtb
