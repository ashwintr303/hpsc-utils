# Boot Yocto Linux on HPPS from NAND with initramfs (via switch_root)

$(call push-prof)

SHARE += lib-hpps-yocto-nand

include $(CONF)/lib-hpps-yocto-nand/Makefile
include $(CONF)/lib-hpps-linux-nand-switchroot/Makefile

PROF_CONF:=$(CONF)/$(call pop-prof)
