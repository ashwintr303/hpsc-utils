# Second-level base overlay for booting Linux on HPPS

prof: \
	$(BLD_PROF)/hpps/conf.sh \
	$(BLD_PROF)/hpps/u-boot/u-boot.env.bin \
	$(BLD_PROF)/hpps/linux/uImage \
	$(BLD_PROF)/hpps/linux/hpsc.dtb

PROF_DIR=$(CONF_PROF)/hpps-linux

# Base of merged source files; to merge others, an overlay appends file as dep
$(BLD_PROF)/hpps/conf.sh: $(PROF_DIR)/hpps/conf.sh | $(BLD_PROF)/hpps/
$(BLD_PROF)/hpps/u-boot/uboot.env: $(PROF_DIR)/hpps/u-boot/uboot.env | $(BLD_PROF)/hpps/u-boot/
$(BLD_PROF)/hpps/u-boot/hpsc-hpps.dts: $(D_hpps_uboot)/arch/arm/dts/hpsc-hpps.dts | $(BLD_PROF)/hpps/u-boot/
$(BLD_PROF)/hpps/linux/hpsc.dts: $(D_hpps_linux)/arch/arm64/boot/dts/hpsc/hpsc.dts | $(BLD_PROF)/hpps/linux/
$(BLD_PROF)/hpps/linux/initramfs.sh: $(PROF_DIR)/hpps/linux/initramfs.sh | $(BLD_PROF)/hpps/linux/
$(BLD_PROF)/hpps/linux/busybox.initramfs.cpio: $(PROF_DIR)/hpps/linux/initramfs | $(BLD_PROF)/hpps/linux/
$(BLD_PROF)/hpps/linux/yocto/conf/local.conf: $(PROF_DIR)/hpps/linux/yocto/conf/local.conf \
	| $(BLD_PROF)/hpps/linux/yocto/conf/

# Overlays
$(HPPS_BUSYBOX)/.config: $(PROF_DIR)/hpps/busybox/hpsc_hpps_miniconf
$(BLD_PROF)/qemu/env.sh: $(PROF_DIR)/qemu/env.sh
$(BLD_PROF)/trch/syscfg.ini: $(PROF_DIR)/trch/syscfg.ini
$(BLD_PROF)/trch/prof.sram.mem.map: $(PROF_DIR)/trch/sram.mem.map
$(BLD_PROF)/trch/bm.config.mk: $(PROF_DIR)/trch/bm.config.mk
