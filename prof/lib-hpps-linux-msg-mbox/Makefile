# Enable the shared memory backend transport for the HPSC Messaging Interface
# into the HPPS Linux kernel.

$(call push-prof)
# includes
PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/hpps/linux.config: $(PROF_CONF)/hpps/linux.config
$(PROF_BLD)/trch/bm.config.mk: $(PROF_CONF)/trch/bm.config.mk
$(PROF_BLD)/hpps/linux.cpp.dts: private CFLAGS+=-DCONFIG_HPSC_MSG_TP_MBOX=1
