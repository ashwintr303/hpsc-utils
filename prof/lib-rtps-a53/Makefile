# Enable RTPS A53 CPU in Qemu machine model

$(call push-prof)
# includes
PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/qemu/hpsc.cpp.dts: private CFLAGS+=-DCONFIG_RTPS_A53=1
$(PROF_BLD)/qemu/env.sh: $(PROF_CONF)/qemu/env.sh
