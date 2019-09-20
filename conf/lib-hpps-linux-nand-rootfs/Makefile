# Boot HPPS Linux without initramfs: kernel mounts NAND via root= boot arg
#
# This is not a top-level profile, since it does not specify which rootfs
# image to build and boot (e.g. Yocto, etc). A top level profile should
# include this profile, and define a rule for hpps/linux/rootfs.nand.bin.

include $(CONF)/lib-hpps-linux-nand/Makefile

PROF_CONF=$(CONF)/lib-hpps-linux-nand-rootfs

$(PROF_BLD)/hpps/u-boot.env: $(PROF_CONF)/hpps/u-boot.env
