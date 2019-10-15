# Preload BL0 ROM bootloader into TRCH SRAM. BL0 loads SSW TRCH bare-metal app
# from non-volatile off-chip memory, and boot into it. The BM app loads
# binaries from NV mem (slow), and boots HPPS into Busybox on Linux via
# ATF+U-boot.

include $(CONF)/platform/Makefile
include $(CONF)/lib-bl0-trch-bm/Makefile
include $(CONF)/lib-trch-bm-nvmem-boot/Makefile
include $(CONF)/lib-hpps-busybox/Makefile
