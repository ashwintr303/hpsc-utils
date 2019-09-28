# Boot Linux on HPPS from NAND via initramfs (switchroot)

$(call push-prof)

include $(CONF)/lib-hpps-busybox/Makefile
include $(CONF)/lib-hpps-linux-nand/Makefile

PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/hpps/initramfs.fs: $(PROF_CONF)/hpps/initramfs.dir
