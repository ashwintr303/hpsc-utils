# Boot HPPS Linux without initramfs: kernel mounts NAND via root= boot arg
#
# This is not a top-level profile, since it does not specifiy which rootfs
# image to build and boot (e.g. Yocto, etc). A top level profile should
# include this profile, and define a rule for hpps/linux/rootfs.nand.bin.

include $(CONF_PROF)/hpps-linux/Makefile

prof: $(BLD_PROF)/hpps/linux/rootfs.nand.bin

PROF_DIR=$(CONF_PROF)/hpps-linux-nand

$(BLD_PROF)/qemu/env.sh: $(PROF_DIR)/qemu/env.sh
