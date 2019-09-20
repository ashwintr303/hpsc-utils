# Boot Linux on HPPS from NAND via initramfs (switchroot)
#
# This is not a top-level profile, since it does not specifiy which rootfs
# image to build and boot (e.g. Yocto, etc). A top level profile should
# include this profile, and define a rule for hpps/linux/rootfs.nand.bin.

include $(CONF)/lib-hpps-busybox/Makefile
include $(CONF)/lib-hpps-linux-nand/Makefile

PROF_CONF=$(CONF)/lib-hpps-linux-nand-switchroot

$(PROF_BLD)/hpps/initramfs.fs: $(PROF_CONF)/hpps/initramfs.dir
