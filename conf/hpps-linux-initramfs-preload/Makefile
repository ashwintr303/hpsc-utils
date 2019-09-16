# Boot Linux on HPPS into an initramfs image (based on a cpio archive),
# that has been preloaded into DRAM memory by the emulator
#
# This is not a top-level profile, since it does not specifiy which initramfs
# image to build and boot (e.g. Yocto, etc). A top level profile should
# include this profile, and define a rule for hpps/linux/initramfs.uimg.

include $(CONF_PROF)/hpps-linux-initramfs/Makefile

PROF_DIR=$(CONF_PROF)/hpps-linux-initramfs-preload

$(BLD_PROF)/qemu/preload.prof.mem.map: $(PROF_DIR)/qemu/preload.prof.mem.map
