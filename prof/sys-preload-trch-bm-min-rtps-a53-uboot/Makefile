# Preload TRCH SSW Bare-Metal App binary (configured with minimal feature set)
# into TRCH SRAM, and ATF+U-boot binaries into RTPS DRAM by HW emulator
# (fast). Boot TRCH into TRCH SSW Bare-Metal App, boot RTPS into U-boot (up
# to the command prompt).

include $(CONF)/platform/Makefile
include $(CONF)/lib-preload-trch-bm/Makefile
include $(CONF)/lib-trch-bm-preload-boot/Makefile
include $(CONF)/lib-trch-bm-min/Makefile
include $(CONF)/lib-rtps-a53-uboot/Makefile
