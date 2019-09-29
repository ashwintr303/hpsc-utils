# Preload binaries into DRAM by HW emulator (fast), boot TRCH into SSW
# bare-metal app, boot HPPS into Yocto Linux in initramfs image.
# DEPENDS (must be built beforehand): lib-hpps-yocto

include $(CONF)/platform/Makefile
include $(CONF)/lib-trch-bm-preload-boot/Makefile
include $(CONF)/lib-trch-bm/Makefile
include $(CONF)/lib-hpps-yocto-initramfs/Makefile
