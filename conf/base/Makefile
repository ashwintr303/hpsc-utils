# Base configuration on top of which all profiles overlay their config.
#
# NOTE: base is a slightly special profile the differs in:
#    1. it defines order-only dir dependencies for the artifacts
#    2. it is included automatically by the makefile (so that each profile
#       doesn't have to included it explicitly).

prof: \
	$(BLD_PROF)/qemu/qemu-env.sh \
	$(BLD_PROF)/qemu/hpsc-arch.dtb \
	$(BLD_PROF)/qemu/preload.prof.mem.map \
	$(BLD_PROF)/trch/syscfg.bin \
	$(BLD_PROF)/trch/prof.sram.mem.bin \
	$(BARE_METAL)/trch/bld/trch.elf \
	$(BARE_METAL)/rtps/bld/rtps.uimg

# Base of merged source files; to merge others, an overlay appends file as dep
$(BLD_PROF)/qemu/qemu-env.sh: $(CONF_BASE)/qemu/qemu-env.sh | $(BLD_PROF)/qemu/
$(BLD_PROF)/qemu/hpsc-arch.dts: $(QEMU_DT)/hpsc-arch.dts | $(BLD_PROF)/qemu/
$(BLD_PROF)/qemu/preload.prof.mem.map: $(CONF_BASE)/qemu/preload.prof.mem.map | $(BLD_PROF)/qemu/
$(BLD_PROF)/trch/syscfg.ini: $(CONF_BASE)/trch/syscfg.ini | $(BLD_PROF)/trch/
$(BLD_PROF)/trch/prof.sram.mem.map: $(CONF_BASE)/trch/sram.mem.map | $(BLD_PROF)/trch/
$(BLD_PROF)/trch/bm.config.mk: $(CONF_BASE)/trch/bm.config.mk | $(BLD_PROF)/trch/
$(BLD_PROF)/rtps/bm.config.mk: $(CONF_BASE)/rtps/bm.config.mk | $(BLD_PROF)/rtps/
$(BLD_PROF)/zebu/prof.hpps.conf.sh: $(CONF_BASE)/zebu/hpps.conf.sh | $(BLD_PROF)/zebu/
$(BLD_PROF)/zebu/prof.hpps.dram.mem.map: $(CONF_BASE)/zebu/hpps-mem.map | $(BLD_PROF)/zebu/
$(BLD_PROF)/zebu/preload.mem.map: $(CONF_BASE)/zebu/preload.mem.map | $(BLD_PROF)/zebu/
