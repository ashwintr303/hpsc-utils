# Enable A53 Cluster 0 (4 processors) in HPPS in Qemu machine model.

$(call push-prof)

include $(CONF)/lib-hpps-linux-smp/Makefile

PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/hpps/u-boot.env: $(PROF_CONF)/hpps/u-boot.env

$(PROF_BLD)/qemu/hpsc.cpp.dts: private CFLAGS+=\
	-DCONFIG_HPPS_A53_CL0=1 \
	-DCONFIG_HPPS_A53_CL1=0
