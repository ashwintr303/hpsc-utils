# Enable kernel tracing into persistent buffer in HPPS Linux

$(call push-prof)
# includes
PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/hpps/linux.config: $(PROF_CONF)/hpps/linux.config
$(PROF_BLD)/hpps/linux.dtb: private CFLAGS+=-DCONFIG_RAMOOPS=1
