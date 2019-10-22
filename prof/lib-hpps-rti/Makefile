# Enable mailboxes in HPPS (in HPPS Linux and TRCH SSW BM App)

$(call push-prof)
# includes
PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/hpps/linux.config: $(PROF_CONF)/hpps/linux.config
$(PROF_BLD)/trch/bm.config.mk: $(PROF_CONF)/trch/bm.config.mk
$(PROF_BLD)/hpps/linux.dtb: private CFLAGS+=-DCONFIG_RTI_TIMERS=1
$(PROF_BLD)/qemu/hpsc.dtb: private CFLAGS+=-DCONFIG_HPPS_RTI_TIMERS=1
