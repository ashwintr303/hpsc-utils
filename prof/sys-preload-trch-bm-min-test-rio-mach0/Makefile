# Preload TRCH SSW Bare-Metal App binary (configured for minimal feature set)
# and syscfg blob into TRCH SRAM (by emulator), and boot into TRCH SSW
# bare-metal application that will run RapidIO tests on boot as machine
# instance #0 (RIO master, will configure and test against machine #1).

$(call push-prof)

include $(CONF)/sys-preload-trch-bm-min-test-rio/Makefile

PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/qemu/env.sh: $(PROF_CONF)/qemu/env.sh
$(PROF_BLD)/qemu/hpsc.dts: $(PROF_CONF)/qemu/hpsc.dts
$(PROF_BLD)/trch/syscfg.ini: $(PROF_CONF)/trch/syscfg.ini
