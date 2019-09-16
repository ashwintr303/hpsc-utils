# Boot HPPS Linux with full Yocto root file system as an initramfs image
# loaded into DRAM.

include $(CONF_PROF)/hpps-yocto/Makefile
include $(CONF_PROF)/hpps-linux-initramfs/Makefile

PROF_DIR=$(CONF_PROF)/hpps-yocto-initramfs

$(BLD_PROF)/hpps/u-boot/uboot.env: $(PROF_DIR)/hpps/u-boot/uboot.env

$(BLD_PROF)/hpps/linux/initramfs.uimg: $(BLD_PROF)/hpps/linux/prof.yocto.initramfs.uimg
	cp -l $< $@
