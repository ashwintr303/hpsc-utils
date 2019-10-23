# Preload TRCH SSW Bare-Metal App binary (configured with default feature set)
# into TRCH SRAM, and ATF+U-boot+Linux binaries (configured for SMP boot on all
# 8 A53 cores) into HPPS DRAM by HW emulator (fast). Boot TRCH into TRCH SSW
# Bare-Metal App, boot HPPS into Busybox on Linux via U-boot+ATF.

include $(CONF)/sys-preload-trch-bm-hpps-busybox/Makefile
include $(CONF)/lib-hpps-linux-smp8/Makefile
