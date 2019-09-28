# Preload binaries into DRAM by HW emulator (fast), boot TRCH into SSW
# bare-metal app, boot RTPS R52 into Bare-Metal App via U-boot, boot HPPS into
# Yocto Linux in initramfs image.

include $(CONF)/lib-trch-bm-preload-boot/Makefile
include $(CONF)/lib-trch-bm/Makefile
include $(CONF)/lib-r52-uboot-bm/Makefile
include $(CONF)/lib-hpps-yocto-initramfs/Makefile
