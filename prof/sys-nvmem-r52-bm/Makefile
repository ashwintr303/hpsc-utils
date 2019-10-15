# Preload BL0 ROM bootloader into TRCH SRAM. BL0 loads SSW TRCH bare-metal app
# from non-volatile off-chip memory, and boot into it. The BM app loads
# binaries from NV mem (slow), and boots RTPS R52 into SSW bare-metal
# application via U-boot.

include $(CONF)/platform/Makefile
include $(CONF)/lib-bl0-trch-bm/Makefile
include $(CONF)/lib-trch-bm-nvmem-boot/Makefile
include $(CONF)/lib-r52-uboot-bm/Makefile
