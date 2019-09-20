# Preload SSW baremetal application image into TRCH on-chip SRAM (via HW
# emulator), and boot TRCH.

PROF_CONF=$(CONF)/sys-trch-bm

PROF_ARTS += \
	$(PROF_BLD)/trch/prof.sram.mem.bin \
	$(PROF_BLD)/trch/syscfg.bin \
	$(PROF_BLD)/trch/bm/trch.elf \
	$(PROF_BLD)/trch/bm/trch.dbg.elf

$(PROF_BLD)/trch/bm.config.mk: $(PROF_CONF)/trch/bm.config.mk
$(PROF_BLD)/trch/syscfg.ini: $(PROF_CONF)/trch/syscfg.ini
$(PROF_BLD)/trch/prof.sram.mem.map: $(PROF_CONF)/trch/prof.sram.mem.map

$(PROF_BLD)/target.sh: $(PROF_CONF)/target.sh
$(PROF_BLD)/qemu/env.sh: $(PROF_CONF)/qemu/env.sh
$(PROF_BLD)/qemu/preload.mem.map: $(PROF_CONF)/qemu/preload.mem.map
