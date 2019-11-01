# Preload BL0 ROM bootloader into TRCH SRAM. BL0 loads TRCH SSW Bare-Metal App
# (configured with default feature set) from non-volatile off-chip memory into
# TRCH SRAM, and boots into it. The TRCH SSW BM app loads RTPS R52 U-boot
# binary and RTPS R52 SSW Bare-Metal App binary (configured with default
# feature set) from NV mem into RTPS DRAM, and ATF+U-boot+Linux binaries into
# HPPS DRAM. Then TRCH SSW BM App and boots RTPS R52 into U-boot which then
# boots into Bare-Metal App, and HPPS is boots into Busybox on Linux.

include $(CONF)/platform/Makefile
include $(CONF)/lib-bl0-trch-bm/Makefile
include $(CONF)/lib-trch-bm-nvmem-boot/Makefile
include $(CONF)/lib-trch-bm-default/Makefile
include $(CONF)/lib-r52-uboot-bm/Makefile
include $(CONF)/lib-r52-bm-default/Makefile
include $(CONF)/lib-hpps-busybox/Makefile
