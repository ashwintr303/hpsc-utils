# Preload binaries into DRAM by HW emulator (fast), boot TRCH into SSW
# bare-metal app, boot HPPS into Yocto Linux mounted in NAND memory.
# DEPENDS (must be built beforehand): lib-hpps-yocto-nand

include $(CONF)/platform/Makefile
include $(CONF)/lib-trch-bm-preload-boot/Makefile
include $(CONF)/lib-trch-bm/Makefile
include $(CONF)/lib-hpps-yocto-nand-rootfs/Makefile
