# Preload TRCH SSW Bare-Metal App binary (configured with minimal feature set)
# into TRCH on-chip SRAM and preload RTPS R52 Bare-Metal Application
# (configured with minimal feature set) to RTPS DRAM. Boot TRCH into SSW BM App
# and have it boot RTPS R52 in split mode with U-boot (up to command prompt) on
# Core 0 (using LSIO 1 UART) and RTPS SSW Bare-Metal application on Core 1
# (using either HPPS UART or LSIO 0 UART (with no UART for TRCH) -- depending
# on the choice made in this profile definition).

$(call push-prof)

include $(CONF)/platform/Makefile
include $(CONF)/lib-trch-bm-min/Makefile
include $(CONF)/lib-preload-trch-bm/Makefile
include $(CONF)/lib-trch-bm-preload-boot/Makefile

include $(CONF)/lib-rtps-r52-split-0/Makefile
include $(CONF)/lib-r52-uboot-core0/Makefile

include $(CONF)/lib-rtps-r52-split-1/Makefile
include $(CONF)/lib-r52-bm-min/Makefile
include $(CONF)/lib-r52-bm/Makefile
include $(CONF)/lib-r52-bm-split/Makefile
include $(CONF)/lib-r52-bm-core1/Makefile

PROF_CONF:=$(CONF)/$(call pop-prof)

# There are not enough LSIO UARTs, so support two options:
#   Option A: TRCH=LSIO 0, R52-core0: LSIO 1, R52-core1: HPPS
#   Option B: TRCH=no uart, R52-core0: LSIO 1, R52-core1: LSIO 0

$(PROF_BLD)/rtps/r52/bm.config.mk: $(PROF_CONF)/rtps/r52/bm.config.mk
$(PROF_BLD)/trch/bm.config.mk: $(PROF_CONF)/trch/bm.config.mk
$(PROF_BLD)/qemu/env.sh: $(PROF_CONF)/qemu/env.sh
