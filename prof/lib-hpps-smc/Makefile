# Enable the single SMC-353 controller in HPPS

$(call push-prof)
# includes
PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/hpps/linux.config: $(PROF_CONF)/hpps/linux.config
$(PROF_BLD)/hpps/linux.dtb: private CFLAGS+=-DCONFIG_SMC=1
$(PROF_BLD)/qemu/hpsc.dtb: private CFLAGS+=-DCONFIG_HPPS_SMC=1
$(PROF_BLD)/mem.ini: $(PROF_CONF)/mem.ini
