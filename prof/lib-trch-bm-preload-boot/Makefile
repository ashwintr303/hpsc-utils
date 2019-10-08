# Have TRCH boot subsystems without loading their binaries into DRAM,
# expecting that the binaries have been preloaded by the HW emulator.

$(call push-prof)

# TODO: order issue, trch.elf needs to be preloaded last, because Qemu sets PC
# this is already fix in Qemu v4 rebase.
#include $(CONF)/lib-trch-bm/Makefile

PROF_CONF:=$(CONF)/$(call pop-prof)

# Small amount of configuration to enable preloaded boot
$(PROF_BLD)/trch/bm.config.mk: $(PROF_CONF)/trch/bm.config.mk
$(PROF_BLD)/trch/syscfg.ini: $(PROF_CONF)/trch/syscfg.ini

# This profile introduces this file, so it provides directory rule
$(PROF_BLD)/preload-boot.preload.mem.map: | $(PROF_BLD)/
# If this profile was included, then preload the conditionally preloaded maps
$(PROF_BLD)/preload.mem.map: $(PROF_CONF)/preload.mem.map \
                             $(PROF_BLD)/preload-boot.preload.mem.map
