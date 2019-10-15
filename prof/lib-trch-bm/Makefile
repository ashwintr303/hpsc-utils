# Preload SSW baremetal application image into TRCH on-chip SRAM (via HW
# emulator), and boot TRCH.

$(call push-prof)
# includes
PROF_CONF:=$(CONF)/$(call pop-prof)

# Debug files are not a dependency of anything, so have to add explicitly
PROF_ARTS += $(PROF_BLD)/trch/bm/trch.dbg.elf

$(PROF_BLD)/trch/bm.config.mk: $(PROF_CONF)/trch/bm.config.mk
$(PROF_BLD)/trch/syscfg.ini: $(PROF_CONF)/trch/syscfg.ini

$(PROF_BLD)/qemu/env.sh: $(PROF_CONF)/qemu/env.sh
