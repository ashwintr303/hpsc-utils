# Enable HPPS SMC-353 memory controller hardware in Qemu. Preload TRCH SSW
# Bare-Metal App binary (configured with minimal feature set) into TRCH SRAM,
# and ATF+U-boot+Linux binaries into HPPS DRAM by HW emulator (fast). Boot TRCH
# into TRCH SSW Bare-Metal App, boot HPPS into Busybox on Linux (configured
# with SMC-353 and NAND drivers and device tree nodes) via U-boot+ATF.

include $(CONF)/sys-preload-trch-bm-min-hpps-booti-busybox/Makefile
include $(CONF)/lib-hpps-smc/Makefile
