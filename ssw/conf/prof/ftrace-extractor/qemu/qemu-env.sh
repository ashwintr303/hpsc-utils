PROF=$PROF_DIR/ftrace-extractor

HPPS_DT=$PROF/hpps/prof.hpps-linux.dtb
HPPS_BL_DT=$PROF/hpps/prof.hpps-uboot.dtb

HPPS_RAMOOPS=hpps-ramoops.bin

# Must match reserved memory nodes in Linux device tree
HPPS_RAMOOPS_ADDR=0x83200000
HPPS_RAMOOPS_SIZE=0x400000

# Must match memory nodes in gp-mem.dts Linux device tree overlay
HPPS_GPBUF_ADDR=0x0200000000
