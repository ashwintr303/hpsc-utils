# Enable HPSC Messaging Interface into HPPS kernel

$(call push-prof)
# includes
PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/hpps/linux.config: $(PROF_CONF)/hpps/linux.config
$(PROF_BLD)/trch/bm.config.mk: $(PROF_CONF)/trch/bm.config.mk
$(PROF_BLD)/hpps/linux.cpp.dts: private CFLAGS+=-DCONFIG_SHMEM=1
