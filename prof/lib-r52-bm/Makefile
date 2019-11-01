# Boot bare-metal applcation on RTPS without a bootloader

$(call push-prof)
# includes
PROF_CONF:=$(CONF)/$(call pop-prof)

PROF_ARTS += $(PROF_BLD)/rtps/r52/bm/rtps.dbg.elf

$(PROF_BLD)/trch/boot.sfs.mem.map: $(PROF_CONF)/trch/boot.sfs.mem.map

$(PROF_BLD)/preload-boot.preload.mem.map: $(PROF_CONF)/preload-boot.preload.mem.map

$(PROF_BLD)/rtps/r52/bm.config.mk: $(PROF_CONF)/rtps/r52/bm.config.mk

$(PROF_BLD)/qemu/env.sh: $(PROF_CONF)/qemu/env.sh
