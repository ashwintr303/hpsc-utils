# Configure TRCH BM app to boot RTPS R52 in SMP mode, i.e. reset Core 0 and
# listen for (PSCI) request from R52 Core 0 to reset Core 1.

$(call push-prof)

include $(CONF)/lib-rtps-r52/Makefile

PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/trch/syscfg.ini: $(PROF_CONF)/trch/syscfg.ini
