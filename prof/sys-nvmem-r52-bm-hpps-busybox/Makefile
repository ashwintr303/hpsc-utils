# Preload BL0 ROM bootloader into TRCH SRAM. BL0 loads SSW TRCH bare-metal app
# from non-volatile off-chip memory into TRCH SRAM, and boots into it. The BM
# app loads binaries from NV mem (slow) into DRAM, and boots RTPS R52 into
# bare-metal app via U-boot, and boots HPPS into Busybox.

include $(CONF)/platform/Makefile
include $(CONF)/lib-bl0-trch-bm/Makefile
include $(CONF)/lib-trch-bm-nvmem-boot/Makefile
include $(CONF)/lib-r52-uboot-bm/Makefile
include $(CONF)/lib-hpps-busybox/Makefile
