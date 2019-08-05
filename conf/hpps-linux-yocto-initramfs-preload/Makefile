# Like hps-linux-yocto-initramfs, but with boot images preloaded into DRAM by the
# emulator as opposed to being stored in TRCH non-volatile memory.

include $(CONF_PROF)/dram-boot/Makefile
include $(CONF_PROF)/hpps-linux-dram/Makefile

PROF_DIR=$(CONF_PROF)/hpps-linux-dram-rootfs-preload

$(BLD_PROF)/qemu/preload.prof.mem.map: $(PROF_DIR)/qemu/preload.prof.mem.map
