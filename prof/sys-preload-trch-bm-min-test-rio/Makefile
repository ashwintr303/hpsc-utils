# Preload TRCH SSW Bare-Metal App binary (configured for minimal feature set)
# and syscfg blob into TRCH SRAM (by emulator), and boot into TRCH SSW
# bare-metal application that will run local RapidIO tests.

$(call push-prof)

include $(CONF)/platform/Makefile
include $(CONF)/lib-preload-trch-bm/Makefile
include $(CONF)/lib-trch-bm-min/Makefile

PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/qemu/hpsc.cpp.dts: private CFLAGS+=-DCONFIG_TRCH_DMA
$(PROF_BLD)/trch/bm.config.mk: $(PROF_CONF)/trch/bm.config.mk
$(PROF_BLD)/trch/syscfg.ini: $(PROF_CONF)/trch/syscfg.ini
