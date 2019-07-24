# Boot HPPS Linux without initramfs: kernel mounts NAND via root= boot arg

prof: $(BLD_PROF)/hpps/rootfs.nand.bin

include $(CONF_PROF)/dram-boot/Makefile
include $(CONF_PROF)/hpps-linux-yocto/Makefile

PROF_DIR=$(CONF_PROF)/hpps-linux-nand

$(BLD_PROF)/qemu/env.sh: $(PROF_DIR)/qemu/env.sh
$(BLD_PROF)/hpps/u-boot/uboot.env: $(PROF_DIR)/hpps/u-boot/uboot.env
