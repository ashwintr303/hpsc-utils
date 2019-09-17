# Boot bare-metal applcation on RTPS

include $(CONF_PROF)/rtps-bl/Makefile

PROF_DIR=$(CONF_PROF)/rtps-bm

prof: $(D_bare_metal)/rtps/bld/rtps.uimg

# Base
$(BLD_PROF)/rtps/bm.config.mk: $(CONF_BASE)/rtps/bm.config.mk | $(BLD_PROF)/rtps/

# Overlays
$(BLD_PROF)/trch/prof.sram.mem.map: $(PROF_DIR)/trch/sram.mem.map
