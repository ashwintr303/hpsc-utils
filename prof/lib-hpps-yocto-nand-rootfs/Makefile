# Boot Yocto Linux on HPPS from NAND without initramfs (via root= boot arg)

$(call push-prof)

SHARE += lib-hpps-yocto-nand

include $(CONF)/lib-hpps-yocto-nand/Makefile
include $(CONF)/lib-hpps-linux-nand-rootfs/Makefile

PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/hpps/u-boot.env: $(PROF_CONF)/hpps/u-boot.env
