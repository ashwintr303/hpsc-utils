# Configure TRCH BM app to start both RTPS R52 cores in SMP mode

$(call push-prof)
include $(CONF)/lib-rtps-r52/Makefile
PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/trch/syscfg.ini: $(PROF_CONF)/trch/syscfg.ini

$(PROF_BLD)/trch/bm.config.mk: $(PROF_CONF)/trch/bm.config.mk
$(PROF_BLD)/rtps/r52/bm.config.mk: $(PROF_CONF)/rtps/r52/bm.config.mk

$(PROF_BLD)/qemu/hpsc.dts: $(PROF_CONF)/qemu/hpsc.dts
$(PROF_BLD)/qemu/hpsc.cpp.dts: private CFLAGS+=-DCONFIG_LSIO_MAILBOX=1
