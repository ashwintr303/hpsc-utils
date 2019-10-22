# Setup for default config of RTPS R52 SSW Bare-Metal Application

$(call push-prof)
# includes
PROF_CONF:=$(CONF)/$(call pop-prof)

# The BM app default config is tracked in the RTPS R52 BM repo, what we need to
# do here is to enable the hardware that is being used by the default config.
$(PROF_BLD)/qemu/hpsc.cpp.dts: private CFLAGS+=$(patsubst %,-D%=1,\
		CONFIG_RTPS_R52_WDTS \
		CONFIG_LSIO_MAILBOX \
		CONFIG_HPPS_MAILBOX_1 \
	)

$(PROF_BLD)/trch/bm.config.mk: $(PROF_CONF)/trch/bm.config.mk
