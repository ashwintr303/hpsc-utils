# Boot HPPS Linux without initramfs: kernel mounts NAND via root= boot arg
#
# This is not a top-level profile, since it does not specifiy which rootfs
# image to build and boot (e.g. Yocto, etc). A top level profile should
# include this profile, and define a rule for hpps/linux/rootfs.nand.bin.

include $(CONF)/lib-hpps-linux/Makefile

# TODO: auto extract deps from env.sh files? ok with mem.map but iffy with env.sh
# Eventually the nv mem images will also be passed in a mem map.
PROF_ARTS += $(PROF_BLD)/hpps/prof.rootfs.nand.bin

PROF_CONF=$(CONF)/lib-hpps-linux-nand

$(PROF_BLD)/qemu/env.sh: $(PROF_CONF)/qemu/env.sh
