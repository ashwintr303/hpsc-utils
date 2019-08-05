# Second-level base overlay for booting Linux on HPPS

prof: \
	$(BLD_PROF)/hpps/conf.sh \
	$(BLD_PROF)/hpps/u-boot/uboot.env.bin \
	$(BLD_PROF)/hpps/linux/uImage

PROF_DIR=$(CONF_PROF)/hpps-linux

# Base of merged source files; to merge others, an overlay appends file as dep
$(BLD_PROF)/hpps/conf.sh: $(PROF_DIR)/hpps/conf.sh | $(BLD_PROF)/hpps/
$(BLD_PROF)/hpps/u-boot/uboot.env: $(PROF_DIR)/hpps/u-boot/uboot.env | $(BLD_PROF)/hpps/u-boot/
$(BLD_PROF)/hpps/u-boot/hpsc-hpps.dts: $(HPPS_UBOOT)/arch/arm/dts/hpsc-hpps.dts | $(BLD_PROF)/hpps/u-boot/
$(BLD_PROF)/hpps/linux/hpsc.dts: $(HPPS_LINUX_BOOT)/dts/hpsc/hpsc.dts | $(BLD_PROF)/hpps/linux/
$(BLD_PROF)/hpps/linux/initramfs.sh: $(PROF_DIR)/hpps/linux/initramfs.sh | $(BLD_PROF)/hpps/linux/
$(BLD_PROF)/hpps/linux/early.initramfs.cpio: $(PROF_DIR)/hpps/linux/initramfs | $(BLD_PROF)/hpps/linux/
$(BLD_PROF)/hpps/linux/yocto/conf/local.conf: $(PROF_DIR)/hpps/linux/yocto/conf/local.conf \
	| $(BLD_PROF)/hpps/linux/yocto/conf/
