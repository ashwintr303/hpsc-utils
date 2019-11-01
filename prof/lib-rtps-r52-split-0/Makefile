# Configure TRCH BM app to start RTPS R52 core 0 in split mode

$(call push-prof)

include $(CONF)/lib-rtps-r52/Makefile

PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/trch/syscfg.ini: $(PROF_CONF)/trch/syscfg.ini
