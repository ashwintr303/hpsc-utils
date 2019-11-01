# Preload TRCH SSW Bare-Metal App binary (configured with minimal feature set)
# into TRCH on-chip SRAM and preload RTPS R52 Bare-Metal Application
# (configured with minimal feature set) to RTPS DRAM. Boot TRCH into SSW BM App
# and have it boot RTPS R52 in split mode with U-boot and RTPS SSW Bare-Metal
# application on Core 1 (and nothing on core 0 -- core not reset).

include $(CONF)/platform/Makefile
include $(CONF)/lib-trch-bm-min/Makefile
include $(CONF)/lib-preload-trch-bm/Makefile
include $(CONF)/lib-trch-bm-preload-boot/Makefile

include $(CONF)/lib-rtps-r52-split-1/Makefile
include $(CONF)/lib-r52-uboot-core1/Makefile
include $(CONF)/lib-r52-bm-min/Makefile
include $(CONF)/lib-r52-uboot-bm/Makefile
