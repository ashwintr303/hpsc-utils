# Preload BL0 bootloader into TRCH ROM baremetal (via HW emulator)

$(call push-prof)
# includes
PROF_CONF:=$(CONF)/$(call pop-prof)

# Debug files are not a dependency of anything, so have to add explicitly
PROF_ARTS += $(PROF_BLD)/trch/bl0/bl0.dbg.elf

$(PROF_BLD)/trch/bl0.config.mk: $(PROF_CONF)/trch/bl0.config.mk

$(PROF_BLD)/preload.mem.map: $(PROF_CONF)/preload.mem.map
$(PROF_BLD)/qemu/env.sh: $(PROF_CONF)/qemu/env.sh

$(PROF_BLD)/trch/bl0cfg.ini: $(PROF_CONF)/trch/bl0cfg.ini
