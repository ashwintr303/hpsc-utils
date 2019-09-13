# Base configuration on top of which all profiles overlay their config.
#
# NOTE: base is a slightly special profile the differs in:
#    1. it defines order-only dir dependencies for the artifacts
#    2. it is included automatically by the makefile (so that each profile
#       doesn't have to included it explicitly).

prof: \
	$(BLD_PROF)/qemu/env.sh \
	$(BLD_PROF)/qemu/hpsc-arch.dtb \
	$(BLD_PROF)/qemu/preload.prof.mem.map \
	$(BLD_PROF)/zebu/env.sh \
	$(BLD_PROF)/zebu/preload.mem.map \
	$(BLD_PROF)/trch/syscfg.bin \
	$(BLD_PROF)/trch/prof.sram.mem.bin \
	$(BARE_METAL)/trch/bld/trch.elf \
	$(BARE_METAL)/rtps/bld/rtps.uimg \
	$(BLD_PROF)/hpps/conf.sh \
	$(BLD_PROF)/hpps/u-boot/uboot.env.bin \
	$(BLD_PROF)/hpps/linux/uImage \
	$(BLD_PROF)/hpps/linux/initramfs.sh \
	$(BLD_PROF)/hpps/linux/initramfs.uimg \
	$(BLD_PROF)/hpps/linux/yocto/conf/local.conf \
	$(BLD_PROF)/hpps/linux/yocto/conf/bblayers.conf

# Base of merged source files; to merge others, an overlay appends file as dep
$(BLD_PROF)/qemu/env.sh: $(CONF_BASE)/qemu/env.sh | $(BLD_PROF)/qemu/
$(BLD_PROF)/qemu/hpsc-arch.dts: $(QEMU_DT)/hpsc-arch.dts | $(BLD_PROF)/qemu/
$(BLD_PROF)/qemu/preload.prof.mem.map: $(CONF_BASE)/qemu/preload.prof.mem.map | $(BLD_PROF)/qemu/
$(BLD_PROF)/trch/syscfg.ini: $(CONF_BASE)/trch/syscfg.ini | $(BLD_PROF)/trch/
$(BLD_PROF)/trch/prof.sram.mem.map: $(CONF_BASE)/trch/sram.mem.map | $(BLD_PROF)/trch/
$(BLD_PROF)/trch/bm.config.mk: $(CONF_BASE)/trch/bm.config.mk | $(BLD_PROF)/trch/
$(BLD_PROF)/rtps/bm.config.mk: $(CONF_BASE)/rtps/bm.config.mk | $(BLD_PROF)/rtps/
$(BLD_PROF)/hpps/conf.sh: $(CONF_BASE)/hpps/conf.sh | $(BLD_PROF)/hpps/
$(BLD_PROF)/hpps/u-boot/uboot.env: $(CONF_BASE)/hpps/u-boot/uboot.env | $(BLD_PROF)/hpps/u-boot/
$(BLD_PROF)/hpps/u-boot/hpsc-hpps.dts: $(HPPS_UBOOT)/arch/arm/dts/hpsc-hpps.dts | $(BLD_PROF)/hpps/u-boot/
$(BLD_PROF)/hpps/linux/hpsc.dts: $(HPPS_LINUX_BOOT)/dts/hpsc/hpsc.dts | $(BLD_PROF)/hpps/linux/
$(BLD_PROF)/hpps/linux/initramfs.sh: $(CONF_BASE)/hpps/linux/initramfs.sh | $(BLD_PROF)/hpps/linux/
$(BLD_PROF)/hpps/linux/initramfs.cpio: $(CONF_BASE)/hpps/linux/initramfs | $(BLD_PROF)/hpps/linux/
$(BLD_PROF)/hpps/linux/yocto/conf/local.conf: $(CONF_BASE)/hpps/linux/yocto/conf/local.conf \
	| $(BLD_PROF)/hpps/linux/yocto/conf/
$(BLD_PROF)/zebu/prof.hpps.conf.sh: $(CONF_BASE)/zebu/hpps.conf.sh | $(BLD_PROF)/zebu/
$(BLD_PROF)/zebu/env.sh: $(CONF_BASE)/zebu/env.sh | $(BLD_PROF)/zebu/
$(BLD_PROF)/zebu/prof.hpps.dram.mem.map: $(CONF_BASE)/zebu/hpps-mem.map | $(BLD_PROF)/zebu/
$(BLD_PROF)/zebu/preload.mem.map: $(CONF_BASE)/zebu/preload.mem.map | $(BLD_PROF)/zebu/
