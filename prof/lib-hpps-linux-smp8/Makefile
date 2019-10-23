# Configure HPPS Linux to boot on all 8 cores of both A53 clusters.

$(call push-prof)
include $(CONF)/lib-hpps-linux-smp/Makefile
PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/qemu/hpsc.cpp.dts: private CFLAGS+=\
	-DCONFIG_HPPS_A53_CL0=1 \
	-DCONFIG_HPPS_A53_CL1=1
