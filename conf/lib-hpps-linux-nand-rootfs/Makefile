# Boot HPPS Linux without initramfs: kernel mounts NAND via root= boot arg

$(call push-prof)

include $(CONF)/lib-hpps-linux-nand/Makefile

PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/hpps/u-boot.env: $(PROF_CONF)/hpps/u-boot.env
