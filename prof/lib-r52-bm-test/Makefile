$(call push-prof)
#includes
PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/rtps/r52/bm.config.mk: $(PROF_CONF)/rtps/r52/bm.config.mk

# Enable hardware not enabled by default config (i.e. hardware
# that the RTPS BM application can test but does not use).
$(PROF_BLD)/qemu/hpsc.dtb: private CFLAGS+=$(patsubst %,-D%=1,\
		CONFIG_RTPS_R52_RTI_TIMERS \
	)
