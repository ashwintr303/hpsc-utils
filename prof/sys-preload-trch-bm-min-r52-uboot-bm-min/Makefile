# Preload TRCH SSW Bare-Metal App binary (configured with minimal feature set)
# into TRCH on-chip SRAM and preload RTPS R52 Bare-Metal Application
# (configured with minimal feature set) to RTPS DRAM. Boot TRCH into SSW BM App
# and have it boot RTPS R52 into U-boot, which then boots into SSW BM App.

include $(CONF)/platform/Makefile
include $(CONF)/lib-trch-bm-min/Makefile
include $(CONF)/lib-preload-trch-bm/Makefile
include $(CONF)/lib-trch-bm-preload-boot/Makefile
include $(CONF)/lib-r52-uboot-bm/Makefile
include $(CONF)/lib-r52-bm-min/Makefile
