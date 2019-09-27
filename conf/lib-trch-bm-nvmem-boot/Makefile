# Have TRCH load binaries for subsystems from non-volatile memory.

# TODO: order issue, trch.elf needs to be preloaded last, because Qemu sets PC
# this is already fix in Qemu v4 rebase.
#include $(CONF)/lib-trch-bm/Makefile

PROF_CONF=$(CONF)/lib-trch-bm-nvmem-boot

$(PROF_BLD)/trch/syscfg.ini: $(PROF_CONF)/trch/syscfg.ini

# "Simple" File System definition (via a map) and the image: stores boot binaries

$(PROF_BLD)/trch/boot.sfs.ini: $(PROF_CONF)/trch/boot.sfs.ini | $(PROF_BLD)/trch/

$(PROF_BLD)/trch/boot.sfs.mem.map: | $(PROF_BLD)/trch/
$(PROF_BLD)/trch/boot.sfs.mem.bin: $(PROF_BLD)/trch/boot.sfs.mem.map

# Add it to artifact list for the dependency scanner to look throuh it
PROF_ARTS += $(PROF_BLD)/trch/boot.sfs.mem.map

$(PROF_BLD)/preload.mem.map: $(PROF_CONF)/preload.mem.map
