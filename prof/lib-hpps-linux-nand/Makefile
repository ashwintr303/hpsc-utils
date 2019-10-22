# Preload HPPS Linux root filesystem image into NAND memory
#
# This is not a top-level profile, since it does not specify which rootfs
# image to build and boot (e.g. Yocto, etc). A top level profile should
# include this profile, and define a rule for hpps/linux/rootfs.nand.bin.

$(call push-prof)

include $(CONF)/lib-hpps-smc/Makefile
include $(CONF)/lib-hpps-linux/Makefile

PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/preload.mem.map: $(PROF_CONF)/preload.mem.map
$(PROF_BLD)/hpps/rootfs.jffs2.conf.sh: $(PROF_CONF)/hpps/rootfs.jffs2.conf.sh
