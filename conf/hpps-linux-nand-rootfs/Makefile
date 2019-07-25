prof: $(BLD_PROF)/hpps/rootfs.nand.bin

include $(CONF_PROF)/hpps-linux-early-initramfs/Makefile
include $(CONF_PROF)/hpps-linux-yocto/Makefile

PROF_DIR=$(CONF_PROF)/hpps-linux-nand-rootfs

$(BLD_PROF)/qemu/env.sh: $(PROF_DIR)/qemu/env.sh
$(BLD_PROF)/hpps/linux/initramfs.cpio: $(PROF_DIR)/hpps/linux/initramfs
