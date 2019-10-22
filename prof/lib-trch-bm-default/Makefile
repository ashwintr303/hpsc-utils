# Configure TRCH Bare-Metal App with the default config (most functionality
# enabled).

$(call push-prof)

# We do need interrupt controllers from all subsystems since we want to use
# hardware blocks that are connected to those subsystems. In other words, the
# default (full) config of TRCH BM SSW app only makes sense when the machine
# has all subsystems and most hardware. These includes enable the
# CPUs+interrupt controllers and the flags below enable the rest. If you want
# to boot TRCH only, then use lib-trch-bm-min instead.
include $(CONF)/lib-rtps-r52/Makefile
include $(CONF)/lib-rtps-a53/Makefile
include $(CONF)/lib-hpps-a53/Makefile

PROF_CONF:=$(CONF)/$(call pop-prof)

# The BM app default config is tracked in the TRCH BM repo, what we need to do
# here is to enable the hardware that is being used by the default config.
$(PROF_BLD)/qemu/hpsc.cpp.dts: private CFLAGS+=$(patsubst %,-D%=1,\
		CONFIG_TRCH_WDTS \
		CONFIG_RTPS_R52_WDTS \
		CONFIG_RTPS_A53_WDTS \
		CONFIG_HPPS_WDTS \
		CONFIG_TRCH_DMA \
		CONFIG_LSIO_SMC \
		CONFIG_LSIO_MAILBOXES \
		CONFIG_HPPS_MAILBOXES \
	)
