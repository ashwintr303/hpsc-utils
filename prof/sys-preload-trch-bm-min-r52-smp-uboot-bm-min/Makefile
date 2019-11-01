# Preload TRCH SSW Bare-Metal App (configured with minimal feature set) into
# TRCH on-chip SRAM and preload RTPS R52 SSW Bare-Metal App (configured in
# SMP mode and minimal feature set) into RTPS DRAM (by emulator). Boot TRCH
# into SSW BM App and have it boot RTPS R52 into U-boot, which then loads the
# SSW BM App.

include $(CONF)/platform/Makefile
include $(CONF)/lib-preload-trch-bm/Makefile
include $(CONF)/lib-trch-bm-preload-boot/Makefile
include $(CONF)/lib-trch-bm-min/Makefile

include $(CONF)/lib-rtps-r52-smp/Makefile
include $(CONF)/lib-r52-uboot-core0/Makefile
include $(CONF)/lib-r52-uboot-bm/Makefile
include $(CONF)/lib-r52-bm-min/Makefile
include $(CONF)/lib-r52-bm-smp/Makefile
