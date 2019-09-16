# Boot Linux on HPPS into an initramfs image (based on a cpio archive).
#
# This is not a top-level profile, since it does not specifiy which initramfs
# image to build and boot (e.g. Yocto, etc). A top level profile should
# include this profile, and define a rule for hpps/linux/initramfs.uimg.

include $(CONF_PROF)/hpps-linux/Makefile

prof: $(BLD_PROF)/hpps/linux/initramfs.uimg

PROF_DIR=$(CONF_PROF)/hpps-linux-initramfs

$(BLD_PROF)/trch/prof.sram.mem.map: $(PROF_DIR)/trch/sram.mem.map
$(BLD_PROF)/hpps/u-boot/u-boot.env: $(PROF_DIR)/hpps/u-boot/u-boot.env
