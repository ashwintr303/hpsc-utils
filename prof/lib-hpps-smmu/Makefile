# Enable System MMU-500 in HPPS (in Linux)

$(call push-prof)
# includes
PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/hpps/linux.config: $(PROF_CONF)/hpps/linux.config
$(PROF_BLD)/hpps/linux.dtb: private CFLAGS+=-DCONFIG_SMMU=1
$(PROF_BLD)/qemu/hpsc.dtb: private CFLAGS+=-DCONFIG_HPPS_SMMU=1
