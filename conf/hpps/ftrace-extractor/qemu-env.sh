HPPS_BIN_FX=$HPPS_BIN/ftrace-extractor

HPPS_INITRAMFS=$HPPS_BIN_FX/initramfs.uimg
HPPS_RAMOOPS=hpps-ramoops.bin

QEMU_DT_FILE=$HPPS_BIN_FX/fx.hpsc.qemu.dtb
HPPS_DT=$HPPS_BIN_FX/fx.hpps.linux.dtb
HPPS_BL=$HPPS_BIN_FX/hpps/u-boot/u-boot.bin

# Must match reserved memory nodes in Linux device tree
HPPS_RAMOOPS_ADDR=0x83200000
HPPS_RAMOOPS_SIZE=0x400000

# Must match memory nodes in gp-mem.dts Linux device tree overlay
HPPS_GPBUF_ADDR=0x0200000000
