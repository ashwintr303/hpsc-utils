# Boot Yocto Linux on HPPS from NAND without initramfs (via root= boot arg)

include $(CONF_PROF)/hpps-yocto/Makefile
include $(CONF_PROF)/hpps-yocto-nand/Makefile
include $(CONF_PROF)/hpps-linux-nand-rootfs/Makefile

PROF_DIR=$(CONF_PROF)/hpps-yocto-nand-rootfs

$(BLD_PROF)/hpps/u-boot/uboot.env: $(PROF_DIR)/hpps/u-boot/uboot.env
