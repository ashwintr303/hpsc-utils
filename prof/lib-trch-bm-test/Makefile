# Boot TRCH into bare-metal application with test suite run on boot

$(call push-prof)
include $(CONF)/lib-trch-bm-default/Makefile
PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/trch/bm.config.mk: $(PROF_CONF)/trch/bm.config.mk

# Enable hardware not enabled by default config (i.e. hardware
# that the TRCH BM application can test but does not use).
$(PROF_BLD)/qemu/hpsc.cpp.dts: private CFLAGS+=$(patsubst %,-D%=1,\
		CONFIG_TRCH_RTI_TIMERS \
		CONFIG_RTPS_R52_RTI_TIMERS \
		CONFIG_RTPS_A53_RTI_TIMERS \
		CONFIG_HPPS_RTI_TIMERS \
		CONFIG_RTPS_SMMU \
		CONFIG_RTPS_DMA \
	)
