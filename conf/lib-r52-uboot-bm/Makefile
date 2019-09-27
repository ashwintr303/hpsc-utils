# Boot bare-metal applcation on RTPS via U-boot

include $(CONF)/lib-r52-uboot/Makefile

PROF_CONF := $(CONF)/lib-r52-uboot-bm

PROF_ARTS += $(PROF_BLD)/rtps/r52/bm/rtps.dbg.elf

$(PROF_BLD)/trch/boot.sfs.mem.map: $(PROF_CONF)/trch/boot.sfs.mem.map
$(PROF_BLD)/rtps/r52/bm.config.mk: $(PROF_CONF)/rtps/r52/bm.config.mk

$(PROF_BLD)/preload-boot.preload.mem.map: $(PROF_CONF)/preload-boot.preload.mem.map
