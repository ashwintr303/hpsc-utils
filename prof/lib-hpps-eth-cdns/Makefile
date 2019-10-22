# Enable Ethernet NIC of Cadence MACB model in HPPS

$(call push-prof)
include $(CONF)/lib-hpps-eth/Makefile
PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/hpps/linux.config: $(PROF_CONF)/hpps/linux.config
$(PROF_BLD)/hpps/linux.cpp.dts: private CFLAGS+=-DCONFIG_ETH_CDNS=1
$(PROF_BLD)/qemu/hpsc.cpp.dts: private CFLAGS+=-DCONFIG_ETH_CDNS=1
