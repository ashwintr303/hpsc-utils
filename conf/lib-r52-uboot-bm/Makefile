# Boot bare-metal applcation on RTPS via U-boot

include $(CONF)/lib-r52-uboot/Makefile

PROF_CONF := $(CONF)/lib-r52-uboot-bm

PROF_ARTS += $(PROF_BLD)/rtps/r52/bm/rtps.dbg.elf

$(PROF_BLD)/trch/boot.sram.mem.map: $(PROF_CONF)/trch/boot.sram.mem.map
$(PROF_BLD)/rtps/r52/bm.config.mk: $(PROF_CONF)/rtps/r52/bm.config.mk

$(PROF_BLD)/qemu/preloadable.mem.map: $(PROF_CONF)/qemu/preloadable.mem.map
