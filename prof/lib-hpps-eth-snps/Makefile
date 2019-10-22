# Enable Ethernet NIC of Synopsys DWC (aka. STMMAC) model in HPPS

$(call push-prof)
include $(CONF)/lib-hpps-eth/Makefile
PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/hpps/linux.config: $(PROF_CONF)/hpps/linux.config
$(PROF_BLD)/hpps/linux.cpp.dts: private CFLAGS+=-DCONFIG_ETH_SNPS=1
