# Preload TRCH SSW Bare-Metal App binary (configured for minimal feature set)
# and syscfg blob into TRCH SRAM (by emulator), and boot into TRCH SSW
# bare-metal application that will run RapidIO tests on boot.

$(call push-prof)

include $(CONF)/platform/Makefile
include $(CONF)/lib-preload-trch-bm/Makefile
include $(CONF)/lib-trch-bm-min/Makefile

PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/qemu/env.sh: $(PROF_CONF)/qemu/env.sh
$(PROF_BLD)/trch/bm.config.mk: $(PROF_CONF)/trch/bm.config.mk
