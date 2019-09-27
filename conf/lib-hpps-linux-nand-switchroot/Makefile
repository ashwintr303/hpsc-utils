# Boot Linux on HPPS from NAND via initramfs (switchroot)

include $(CONF)/lib-hpps-busybox/Makefile
include $(CONF)/lib-hpps-linux-nand/Makefile

PROF_CONF=$(CONF)/lib-hpps-linux-nand-switchroot

$(PROF_BLD)/hpps/initramfs.fs: $(PROF_CONF)/hpps/initramfs.dir
