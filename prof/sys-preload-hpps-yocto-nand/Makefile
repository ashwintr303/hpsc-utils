# Preload binaries into DRAM by HW emulator (fast), boot TRCH into SSW
# bare-metal app, boot HPPS into Yocto Linux mounted in NAND memory.

include $(CONF)/platform/Makefile
include $(CONF)/lib-preload-trch-bm/Makefile
include $(CONF)/lib-trch-bm-preload-boot/Makefile
SHARE += lib-hpps-yocto
include $(CONF)/lib-hpps-yocto/Makefile
include $(CONF)/lib-hpps-linux-nand-rootfs/Makefile
