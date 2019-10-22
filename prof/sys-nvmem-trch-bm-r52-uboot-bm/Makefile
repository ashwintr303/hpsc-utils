# Preload BL0 ROM bootloader into TRCH SRAM. BL0 loads TRCH SSW Bare-Metal App
# (configured with default feature set) from non-volatile off-chip memory, and
# boot into it. The TRCH BM app loads RTPS R52 U-boot binary and RTPS R52 SSW
# Bare-Metal App binary (configured with default feature set) from NV mem,
# and boots RTPS R52 into SSW Bare-Metal Application.

include $(CONF)/platform/Makefile
include $(CONF)/lib-bl0-trch-bm/Makefile
include $(CONF)/lib-trch-bm-nvmem-boot/Makefile
include $(CONF)/lib-trch-bm-default/Makefile
include $(CONF)/lib-r52-uboot-bm/Makefile
include $(CONF)/lib-r52-bm-default/Makefile
