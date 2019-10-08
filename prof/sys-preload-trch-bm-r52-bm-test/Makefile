# Preload TRCH SSW bare metal application into TRCH SRAM and RTPS R52
# SSW bare metal application into RTPS DRAM (by emulator), boot TRCH with the
# with test suite executed on, and have it boot RTPS R52 into SSW bare-metal
# application with test suite executed on boot.

include $(CONF)/platform/Makefile
include $(CONF)/lib-preload-trch-bm/Makefile
include $(CONF)/lib-trch-bm-preload-boot/Makefile
include $(CONF)/lib-trch-bm-test/Makefile
include $(CONF)/lib-r52-uboot-bm/Makefile
include $(CONF)/lib-r52-bm-test/Makefile
