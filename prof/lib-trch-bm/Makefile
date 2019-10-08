# Preload SSW baremetal application image into TRCH on-chip SRAM (via HW
# emulator), and boot TRCH.

$(call push-prof)
# includes
PROF_CONF:=$(CONF)/$(call pop-prof)

# Debug files are not a dependency of anything, so have to add explicitly
PROF_ARTS += $(PROF_BLD)/trch/bm/trch.dbg.elf

$(PROF_BLD)/trch/bm.config.mk: $(PROF_CONF)/trch/bm.config.mk
$(PROF_BLD)/trch/syscfg.ini: $(PROF_CONF)/trch/syscfg.ini

# "Simple" File System definition (via a map) and the image: stores boot binaries
$(PROF_BLD)/trch/boot.sfs.ini: $(PROF_CONF)/trch/boot.sfs.ini \
                               | $(PROF_BLD)/trch/
$(PROF_BLD)/trch/boot.sfs.mem.map: | $(PROF_BLD)/trch/
# Add it to artifact list for the dependency scanner to look throuh it
PROF_ARTS += $(PROF_BLD)/trch/boot.sfs.mem.map

$(PROF_BLD)/qemu/env.sh: $(PROF_CONF)/qemu/env.sh
