# Boot HPPS Linux with full Yocto root file system as an initramfs image
# loaded into DRAM.

prof: $(BLD_PROF)/hpps/linux/yocto.initramfs.uimg

include $(CONF_PROF)/hpps-linux-yocto/Makefile

PROF_DIR=$(CONF_PROF)/hpps-linux-yocto-initramfs

$(BLD_PROF)/hpps/u-boot/uboot.env: $(PROF_DIR)/hpps/u-boot/uboot.env
$(BLD_PROF)/trch/prof.sram.mem.map: $(PROF_DIR)/trch/sram.mem.map
