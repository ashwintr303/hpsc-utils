# Have TRCH load binaries for subsystems from non-volatile memory.

PROF_CONF=$(CONF)/lib-trch-bm-nvmem-boot

$(PROF_BLD)/trch/syscfg.ini: $(PROF_CONF)/trch/syscfg.ini

$(PROF_BLD)/trch/boot.sram.mem.map: | $(PROF_BLD)/trch/

$(PROF_BLD)/trch/prof.sram.mem.map: $(PROF_BLD)/trch/boot.sram.mem.map
