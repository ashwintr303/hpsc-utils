# Preload TRCH SSW Bare-Metal App (configured with default feature set) into
# TRCH on-chip SRAM and preload RTPS R52 SSW Bare-Metal App (configured with
# default feature set) into RTPS DRAM (by emulator). Boot TRCH into SSW BM App
# and have it boot RTPS R52 into U-boot, which then loads the SSW BM App.

include $(CONF)/platform/Makefile
include $(CONF)/lib-preload-trch-bm/Makefile
include $(CONF)/lib-trch-bm-preload-boot/Makefile
include $(CONF)/lib-trch-bm-default/Makefile
include $(CONF)/lib-r52-uboot-bm/Makefile
include $(CONF)/lib-r52-bm-default/Makefile
