# Preload BL0 ROM bootloader into TRCH SRAM. BL0 loads TRCH SSW Bare-Metal App
# (configured with tests to run on boot) # from non-volatile off-chip memory,
# and boot into it. The TRCH SSW BM App runs its tests then loads RTPS R52
# U-boot binary and RTPS R52 SSW Bare-Metal App (configured with tests to run
# on boot) binary from non-volatile memory, and boots RTPS R52 into U-boot
# which then boots the RTPS R52 SSW BM App, which run its tests on boot.

include $(CONF)/platform/Makefile
include $(CONF)/lib-bl0-trch-bm/Makefile
include $(CONF)/lib-trch-bm-nvmem-boot/Makefile
include $(CONF)/lib-trch-bm-test/Makefile
include $(CONF)/lib-r52-uboot-bm/Makefile
include $(CONF)/lib-r52-bm-test/Makefile
