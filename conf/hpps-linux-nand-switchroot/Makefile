# Boot Linux on HPPS from NAND via initramfs (switchroot)
#
# This is not a top-level profile, since it does not specifiy which rootfs
# image to build and boot (e.g. Yocto, etc). A top level profile should
# include this profile, and define a rule for hpps/linux/rootfs.nand.bin.

include $(CONF_PROF)/hpps-busybox-initramfs/Makefile
include $(CONF_PROF)/hpps-linux-nand/Makefile

PROF_DIR=$(CONF_PROF)/hpps-linux-nand-switchroot

$(BLD_PROF)/hpps/linux/initramfs.cpio: $(PROF_DIR)/hpps/linux/initramfs
