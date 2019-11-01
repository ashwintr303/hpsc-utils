# Preload TRCH SSW Bare-Metal App (configured with tests to run on boot) into TRCH
# SRAM and RTPS R52 SSW Bare-Metal App (configured with tests to run on boot)
# into RTPS DRAM (by emulator). Boot TRCH into TRCH SSW BM App, which runs tests,
# then boots RTPS R52 into SSW BM App, which runs tests on boot.

include $(CONF)/platform/Makefile
include $(CONF)/lib-preload-trch-bm/Makefile
include $(CONF)/lib-trch-bm-preload-boot/Makefile
include $(CONF)/lib-trch-bm-test/Makefile
include $(CONF)/lib-r52-uboot-bm/Makefile
include $(CONF)/lib-r52-bm-test/Makefile
