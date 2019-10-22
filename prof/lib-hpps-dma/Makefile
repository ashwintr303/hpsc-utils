# Enable DMA-330 controllers in HPPS (in Linux)

$(call push-prof)
# includes
PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/hpps/linux.config: $(PROF_CONF)/hpps/linux.config
$(PROF_BLD)/hpps/linux.dtb: private CFLAGS+=-DCONFIG_DMA=1
$(PROF_BLD)/qemu/hpsc.dtb: private CFLAGS+=-DCONFIG_HPPS_DMA=1
