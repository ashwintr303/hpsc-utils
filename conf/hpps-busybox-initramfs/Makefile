# Boot HPPS Linux into Busybox (from an initramfs archive).

include $(CONF_PROF)/hpps-linux-initramfs/Makefile

PROF_DIR=$(CONF_PROF)/hpps-yocto-initramfs

$(BLD_PROF)/hpps/linux/initramfs.uimg: $(BLD_PROF)/hpps/linux/busybox.initramfs.uimg
	cp -l $< $@
