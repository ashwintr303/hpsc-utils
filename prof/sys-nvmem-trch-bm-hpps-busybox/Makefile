# Enable Preload BL0 ROM bootloader into TRCH SRAM. BL0 loads TRCH SSW
# Bare-Metal App (configured with default feature set) from non-volatile
# off-chip memory into TRCH SRAM, and boots into it. The TRCH SSW BM app loads
# ATF+U-boot+Linux binaries from non-volatile memory into HPPS DRAM. Then TRCH
# SSW BM App and boots HPPS into Busybox on Linux.

include $(CONF)/platform/Makefile
include $(CONF)/lib-bl0-trch-bm/Makefile
include $(CONF)/lib-trch-bm-nvmem-boot/Makefile
include $(CONF)/lib-trch-bm-default/Makefile
include $(CONF)/lib-hpps-busybox/Makefile
