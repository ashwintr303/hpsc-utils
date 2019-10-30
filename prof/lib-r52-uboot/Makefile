# Second-level base config to load RTPS (through boot loader)

$(call push-prof)

include $(CONF)/lib-rtps-r52/Makefile

PROF_CONF:=$(CONF)/$(call pop-prof)

PROF_ARTS += $(PROF_BLD)/rtps/r52/u-boot/u-boot.dbg.elf

$(PROF_BLD)/rtps/r52/conf.sh: $(PROF_CONF)/rtps/r52/conf.sh
$(PROF_BLD)/rtps/r52/u-boot.env: $(PROF_CONF)/rtps/r52/u-boot.env

$(PROF_BLD)/trch/syscfg.ini: $(PROF_CONF)/trch/syscfg.ini

$(PROF_BLD)/trch/boot.sfs.mem.map: $(PROF_CONF)/trch/boot.sfs.mem.map
$(PROF_BLD)/preload-boot.preload.mem.map: $(PROF_CONF)/preload-boot.preload.mem.map

$(PROF_BLD)/qemu/env.sh: $(PROF_CONF)/qemu/env.sh

# TODO: CPU reset vector should be configurable dynamically by TRCH,
# for now, configure it statically via Qemu DT.
$(PROF_BLD)/qemu/hpsc.dts: $(PROF_CONF)/qemu/hpsc.dts
