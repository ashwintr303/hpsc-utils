# Configure TRCH BM app to start both RTPS R52 cores in lockstep mode

$(call push-prof)

include $(CONF)/lib-rtps-r52/Makefile

PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/trch/syscfg.ini: $(PROF_CONF)/trch/syscfg.ini
