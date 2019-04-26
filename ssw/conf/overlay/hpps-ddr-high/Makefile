OVERLAY=$(CONF)/overlay/hpps-ddr-high

prof: $(BLD_PROF)/hpps/u-boot/hpsc-hpps.dtb

$(BLD_PROF)/qemu/hpsc-arch.dts: $(OVERLAY)/hpps-ddr-high-1.qemu.dts
$(BLD_PROF)/qemu/preload.prof.mem.map: $(OVERLAY)/qemu/preload.prof.mem.map
$(BLD_PROF)/hpps/u-boot/hpsc-hpps.dts: $(OVERLAY)/hpps-ddr-high-1.uboot.dts
$(BLD_PROF)/trch/prof.sram.mem.map: $(OVERLAY)/trch/prof.sram.mem.map
