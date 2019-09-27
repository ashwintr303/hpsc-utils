# Preload SSW baremetal application image into TRCH on-chip SRAM (via HW
# emulator), and boot TRCH.

$(call push-prof)
# includes
PROF_CONF:=$(CONF)/$(call pop-prof)

# Debug files are not a dependency of anything, so have to add explicitly
PROF_ARTS += $(PROF_BLD)/trch/bm/trch.dbg.elf

$(PROF_BLD)/trch/bm.config.mk: $(PROF_CONF)/trch/bm.config.mk
$(PROF_BLD)/trch/syscfg.ini: $(PROF_CONF)/trch/syscfg.ini

$(PROF_BLD)/preload.mem.map: $(PROF_CONF)/preload.mem.map
$(PROF_BLD)/qemu/env.sh: $(PROF_CONF)/qemu/env.sh

# This profile supports two variants, depending on trch-{nvmem,preload}-boot
# profiles; we append to both sets of config files but only one will be used.

# Only trch-preload-boot will apply this map
$(PROF_BLD)/preload-boot.preload.mem.map: $(PROF_CONF)/preload-boot.preload.mem.map

# Only trch-nvmem-boot will build the "Simple" File System with boot images is
# (trch-nvmem-boot owns this file, this profile just adds the syscfg).
$(PROF_BLD)/trch/boot.sfs.mem.map: $(PROF_CONF)/trch/boot.sfs.mem.map
