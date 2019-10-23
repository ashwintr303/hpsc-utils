# Configure HPPS Linux to boot on all cores of both A53 clusters.

$(call push-prof)
# includes
PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/hpps/u-boot.env: $(PROF_CONF)/hpps/u-boot.env

# The mailbox is used by ATF for PSCI (to ask TRCH to reset the secondary cores).
$(PROF_BLD)/qemu/hpsc.cpp.dts: private CFLAGS+=-DCONFIG_HPPS_MAILBOX_0=1
$(PROF_BLD)/hpps/atf: private MAKE_ARGS+=TRCH_SERVER=1
$(PROF_BLD)/trch/bm.config.mk: $(PROF_CONF)/trch/bm.config.mk
