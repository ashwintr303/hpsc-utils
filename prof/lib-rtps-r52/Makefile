# Enable RTPS R52 CPUs in Qemu machine model and instruct TRCH Bare-Metal App
# to boot them.

$(call push-prof)
# includes
PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/trch/syscfg.ini: $(PROF_CONF)/trch/syscfg.ini

$(PROF_BLD)/qemu/hpsc.cpp.dts: private CFLAGS+=-DCONFIG_RTPS_R52=1
