# Preload TRCH SSW Bare-Metal App binary (configured with minimal feature set)
# into TRCH SRAM, and ATF+U-boot+Linux binaries into HPPS DRAM by HW emulator
# (fast). Boot TRCH into TRCH SSW Bare-Metal App, boot HPPS into Busybox on
# Linux via U-boot+ATF.

include $(CONF)/platform/Makefile
include $(CONF)/lib-preload-trch-bm/Makefile
include $(CONF)/lib-trch-bm-min/Makefile
include $(CONF)/lib-trch-bm-preload-boot/Makefile
include $(CONF)/lib-hpps-busybox/Makefile
include $(CONF)/lib-hpps-linux-booti/Makefile
