# Preload HPPS Linux root filesystem image into NAND memory
#
# This is not a top-level profile, since it does not specify which rootfs
# image to build and boot (e.g. Yocto, etc). A top level profile should
# include this profile, and define a rule for hpps/linux/rootfs.nand.bin.

include $(CONF)/lib-hpps-linux/Makefile

PROF_CONF=$(CONF)/lib-hpps-linux-nand

$(PROF_BLD)/preload.mem.map: $(PROF_CONF)/preload.mem.map
