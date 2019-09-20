# Second-level base config to load RTPS (through boot loader)

PROF_CONF := $(CONF)/lib-r52-uboot

PROF_ARTS += $(PROF_BLD)/rtps/r52/u-boot/u-boot.dbg.elf

$(PROF_BLD)/trch/syscfg.ini: $(PROF_CONF)/trch/syscfg.ini
$(PROF_BLD)/trch/boot.sram.mem.map: $(PROF_CONF)/trch/boot.sram.mem.map

$(PROF_BLD)/qemu/env.sh: $(PROF_CONF)/qemu/env.sh
$(PROF_BLD)/qemu/preloadable.mem.map: $(PROF_CONF)/qemu/preloadable.mem.map
