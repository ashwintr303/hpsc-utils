# Boot Yocto Linux on HPPS from NAND without initramfs (via root= boot arg)

include $(CONF_PROF)/hpps-yocto/Makefile
include $(CONF_PROF)/hpps-linux-nand/Makefile

$(BLD_PROF)/hpps/linux/rootfs.nand.bin: $(BLD_PROF)/hpps/linux/prof.yocto.rootfs.nand.bin
	cp -l $< $@
