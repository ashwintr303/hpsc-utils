# Enable an Ethernet NIC in HPPS (model chosen by other profiles)

$(call push-prof)
# includes
PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/hpps/linux.config: $(PROF_CONF)/hpps/linux.config
$(PROF_BLD)/hpps/linux.cpp.dts: private CFLAGS+=-DCONFIG_ETH=1

$(PROF_BLD)/qemu/env.sh: $(PROF_CONF)/qemu/env.sh
