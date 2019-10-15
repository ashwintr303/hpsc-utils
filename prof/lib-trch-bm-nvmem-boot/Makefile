# Have TRCH boot subsystems by loading binaries from NV mem into respective
# DRAM.

$(call push-prof)
# includes
PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/trch/bm.config.mk: $(PROF_CONF)/trch/bm.config.mk
$(PROF_BLD)/trch/syscfg.ini: $(PROF_CONF)/trch/syscfg.ini

$(PROF_BLD)/preload.mem.map: $(PROF_CONF)/preload.mem.map

# "Simple" File System definition (via a map) and the image: stores boot binaries
$(PROF_BLD)/trch/boot.sfs.ini: $(PROF_CONF)/trch/boot.sfs.ini \
                               | $(PROF_BLD)/trch/
$(PROF_BLD)/trch/boot.sfs.mem.map: | $(PROF_BLD)/trch/

# Add it to artifact list for the dependency scanner to look throuh it
PROF_ARTS += $(PROF_BLD)/trch/boot.sfs.mem.map
