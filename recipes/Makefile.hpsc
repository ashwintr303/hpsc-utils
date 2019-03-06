# Relative paths to reduce duplication throughout this file
BSP=hpsc-bsp
TOOLS=$(BSP)/tools
HPPS_ZEBU=$(BSP)/zebu/hpps
HPPS_ATF=arm-trusted-firmware
HPPS_UBOOT=u-boot-a53
HPPS_LINUX=linux-hpsc
HPPS_LINUX_BOOT=$(HPPS_LINUX)/arch/arm64/boot
RTPS_R52_UBOOT=u-boot-r52
RTPS_A53_UBOOT=u-boot-rtps-a53
RTPS_A53_ATF=arm-trusted-firmware-rtps-a53
BARE_METAL=hpsc-baremetal
# Directory for artifacts created by this top-level build
BIN=bin
HPPS_BIN=$(BIN)/hpps
HPPS_ZEBU_BIN=$(HPPS_BIN)/zebu

CROSS_A53=aarch64-poky-linux-
CROSS_R52=arm-none-eabi-
CROSS_M4=arm-none-eabi-

# Settings for build artifacts produced by this top-level builder
HPPS_KERN_LOAD_ADDR=0x8048_0000 # (base + TEXT_OFFSET), where base must be aligned to 2MB
HPPS_DRAM_ADDR=0x8000_0000

HPPS_ZEBU_DDR_IMAGES=$(HPPS_ZEBU_BIN)/ddr0.vhex $(HPPS_ZEBU_BIN)/ddr1.vhex

# Address parsing function, takes addresses with _ separators
addr=$(subst _,,$1)

# Shortcut aliases
#
# Note: all clean targets here are hardest cleans, if you want any other clean,
# then use the build system of the respective component directly.

all: trch rtps hpps
clean: clean-trch clean-rtps clean-hpps
.PHONY: all clean

trch: trch-bm
clean-trch: clean-trch-bm
.PHONY: trch clean-trch

rtps: rtps-r52 rtps-a53
clean-rtps: clean-rtps-r52 clean-rtps-a53
.PHONY: rtps clean-rtps

hpps: hpps-atf hpps-uboot hpps-linux
clean-hpps: clean-hpps-atf clean-hpps-uboot clean-hpps-linux
.PHONY: hpps clean-hpps

rtps-r52: rtps-r52-uboot rtps-r52-bm
clean-rtps-r52: clean-rtps-r52-uboot clean-rtps-r52-bm
.PHONY: rtps-r52 clean-rtps-r52

rtps-a53: rtps-a53-atf rtps-a53-uboot
clean-rtps-a53: clean-rtps-atf clean-rtps-a53-uboot
.PHONY: rtps-a53 clean-rtps-a53

bm: trch-bm rtps-r52-bm
clean-bm: clean-trch-bm clean-rtps-bm
.PHONY: bm clean-bm

$(BIN)/%/:
	mkdir -p "$@"

# Invariant: artifacts have a unique recipe. That unique recipe may part of two
# different dependency trees: (A) the dependency tree for the user interface
# target (aka. an alias), or (B) the dependency tree of another artifact (e.g.
# a memory image). Also we have the requirement that rule for nested artifacts
# trigger the nested dependency build. This won't happen if the rule here
# depends on the artifact (the dep tree would be truncated at that artifact --
# if it exists, no recipe will be invoked, even if its dependencies in the
# nested tree are stale).
#
# This invariant plus the requirements determines the pattern: the recipe for
# invoking the nested dependency building for a nested artifact is associated
# with a phony target. Then, both the user-facing alias (case A) and the
# artifact (case B) both depend on that phony target. Most often there's no
# alias (case A) because the phony target is short enough to be user-facing.
#
# Another non-way to satisfy invariant+requirement would be to use only the
# phony targets for the artifacts here (i.e. eliminate Case B rule), but this
# hinders rule legibility because dependencies can no longer be explicit
# artifacts (they are phony targets) and the recipies can no longer refer to
# dependencies (e.g. via $<).

TRCH_BM_ARGS=-C $(BARE_METAL)/trch
$(BARE_METAL)/trch/bld/trch.elf: trch-bm
trch-bm:
	$(MAKE) $(TRCH_BM_ARGS) ARM_NONE_EABI=$(CROSS_M4)
clean-trch-bm:
	$(MAKE) $(TRCH_BM_ARGS) clean
.PHONY: trch-bm clean-trch-bm

RTPS_R52_BM_ARGS=-C $(BARE_METAL)/rtps
$(BARE_METAL)/rtps/bld/rtps.uimg: rtps-bm
rtps-r52-bm:
	$(MAKE) $(RTPS_R52_BM_ARGS) ARM_NONE_EABI=$(CROSS_R52)
clean-rtps-r52-bm:
	$(MAKE) $(RTPS_R52_BM_ARGS) clean
.PHONY: rtps-r52-bm clean-rtps-r52-bm

RTPS_R52_UBOOT_MAKE_ARGS=-C $(RTPS_R52_UBOOT) CROSS_COMPILE=$(CROSS_R52)
$(RTPS_R52_UBOOT)/.config:
	$(MAKE) $(RTPS_R52_UBOOT_MAKE_ARGS) hpsc_rtps_r52_defconfig
$(RTPS_R52_UBOOT)/u-boot.bin: rtps-r52-uboot
rtps-r52-uboot:
	$(MAKE) $(RTPS_R52_UBOOT_MAKE_ARGS) u-boot.bin
clean-rtps-r52-uboot:
	$(MAKE) $(RTPS_R52_UBOOT_MAKE_ARGS) clean
	rm -f $(RTPS_R52_UBOOT)/.config
.PHONY: rtps-r52-uboot clean-rtps-r52-uboot

RTPS_A53_UBOOT_MAKE_ARGS=-C $(RTPS_A53_UBOOT) CROSS_COMPILE=$(CROSS_A53)
$(RTPS_A53_UBOOT)/.config:
	$(MAKE) $(RTPS_A53_UBOOT_MAKE_ARGS) hpsc_rtps_a53_defconfig
$(RTPS_A53_UBOOT)/u-boot.bin: rtps-a53-uboot
rtps-a53-uboot: $(RTPS_A53_UBOOT)/u-boot.bin
	$(MAKE) $(RTPS_A53_UBOOT_MAKE_ARGS) u-boot.bin
clean-rtps-a53-uboot:
	$(MAKE) $(RTPS_A53_UBOOT_MAKE_ARGS) clean
	rm -f $(RTPS_A53_UBOOT)/.config
.PHONY: rtps-a53-uboot clean-rtps-a53-uboot

RTPS_A53_ATF_MAKE_ARGS=-C $(RTPS_A53_ATF) \
	PLAT=hpsc_rtps_a53 CROSS_COMPILE=$(CROSS_A53)
$(RTPS_A53_ATF)/build/hpsc_rtps_a53/debug/bl31.bin: rtps-a53-atf
rtps-a53-atf:
	$(MAKE) $(RTPS_A53_ATF_MAKE_ARGS) bl31
clean-rtps-a53-atf:
	$(MAKE) $(RTPS_A53_ATF_MAKE_ARGS) clean
.PHONY: rtps-a53-atf clean-rtps-a53-atf

HPPS_ATF_MAKE_ARGS=-C $(HPPS_ATF) PLAT=hpsc CROSS_COMPILE=$(CROSS_A53) 
$(HPPS_ATF)/build/hpsc/debug/bl31.bin: hpps-atf
hpps-atf:
	$(MAKE) $(HPPS_ATF_MAKE_ARGS) bl31
clean-hpps-atf:
	$(MAKE) $(HPPS_ATF_MAKE_ARGS) clean
.PHONY: hpps-atf clean-hpps-atf

HPPS_UBOOT_MAKE_ARGS=-C $(HPPS_UBOOT) CROSS_COMPILE=$(CROSS_A53)
$(HPPS_UBOOT)/.config:
	$(MAKE) $(HPPS_UBOOT_MAKE_ARGS) hpsc_hpps_defconfig
$(HPPS_UBOOT)/u-boot.bin: hpps-uboot
hpps-uboot: $(HPPS_UBOOT)/.config
	$(MAKE) $(HPPS_UBOOT_MAKE_ARGS) u-boot.bin
clean-hpps-uboot:
	$(MAKE) $(HPPS_UBOOT_MAKE_ARGS) clean
	rm -f $(HPPS_UBOOT)/.config
.PHONY: hpps-uboot clean-hpps-uboot

HPPS_LINUX_MAKE_ARGS=-C $(HPPS_LINUX) ARCH=arm64 CROSS_COMPILE=$(CROSS_A53)
$(HPPS_LINUX)/.config:
	$(MAKE) $(HPPS_LINUX_MAKE_ARGS) hpsc_defconfig

$(HPPS_LINUX_BOOT)/Image.gz: $(HPPS_LINUX)/.config
	$(MAKE) $(HPPS_LINUX_MAKE_ARGS) Image.gz

# Note: need to sequence, otherwise whether we have two targets at same
# priority or we have one recipe with multiple artifacts, in both cases will be
# broken with parallel make. We do want explicit references to both artifacts
# in this makefile though, because they both participate in images.
$(HPPS_LINUX_BOOT)/dts/hpsc/hpsc.dtb: $(HPPS_LINUX)/Image.gz
	$(MAKE) $(HPPS_LINUX_MAKE_ARGS) hpsc/hpsc.dtb

$(HPPS_BIN)/uImage: $(HPPS_LINUX_BOOT)/Image.gz | $(HPPS_BIN)/
	mkimage -C gzip -A arm64 -d "$<" -a $(call addr,${HPPS_KERN_LOAD_ADDR}) "$@"

# The make command in this recipe is only used for the invocation from the user
# interface (via hpps-linux phony target shortcut), but not from the dependency
# build of another artifact, for which the above recipes are used (a violation
# of the invariant above). We could eliminate this by adding phony targets for
# Image.gz and hpsc.dtb and have hpps-linux-inner target and the non-phony
# targets for Image.gz, hpsc.dtb artifacts depend on those phony targets. Meh.
hpps-linux-inner: $(HPPS_LINUX)/.config
	$(MAKE) $(HPPS_LINUX_MAKE_ARGS)
hpps-linux: hpps-linux-inner $(HPPS_BIN)/uImage
clean-hpps-linux:
	$(MAKE) $(HPPS_LINUX_MAKE_ARGS) mrproper
	rm -f $(HPPS_BIN)/uImage
.PHONY: hpps-linux-inner hpps-linux clean-hpps-linux

hpps-zebu: $(HPPS_ZEBU_DDR_IMAGES)
.PHONY: hpps-zebu

# Extract dependencies from the map file
$(HPPS_ZEBU_BIN)/mem.dep: $(HPPS_ZEBU)/mem.map  | $(HPPS_ZEBU_BIN)/
	$(TOOLS)/mkmemimg -l $< | sed 's#^#$(HPPS_ZEBU_BIN)/mem.bin: #' > $@

ifeq ($(filter clean-%,$(MAKECMDGOALS)),)
ifneq ($(findstring zebu,$(MAKECMDGOALS)),)
# Ideally, this would be a hard include (without - that ignores errors),
# and the hard include does work, however it generates a warning that
# the file is not found. Switching to soft include to silence that warn.
-include $(HPPS_ZEBU_BIN)/mem.dep
endif
endif

$(HPPS_ZEBU_BIN)/mem.bin: $(HPPS_ZEBU_BIN)/mem.dep
	$(TOOLS)/mkmemimg $(HPPS_ZEBU)/mem.map $@

# Convoluted pattern for multi-artifact recipe that works with parallel make.
# The recipe makes an intermediate artifact .gen, which is then copied.

HPPS_ZEBU_DDR_IMAGES_BIN=$(patsubst %.vhex,%.bin,$(HPPS_ZEBU_DDR_IMAGES))
HPPS_ZEBU_DDR_IMAGES_GEN=$(patsubst %.bin,%.bin.gen,$(HPPS_ZEBU_DDR_IMAGES_BIN))
.SECONDARY: $(HPPS_ZEBU_DDR_IMAGES_BIN) $(HPPS_ZEBU_DDR_IMAGES_GEN)

%.bin: %.bin.gen
	cp -l $< $@

hpps-zebu-ddr-images: $(HPPS_ZEBU_BIN)/mem.bin
	$(TOOLS)/memstripe --base $(HPPS_DRAM_ADDR) -i $< $(HPPS_ZEBU_DDR_IMAGES_GEN)
.INTERMEDIATE: hpps-zebu-ddr-images
define hpps-zebu-ddr-imgage-rule
$1: hpps-zebu-ddr-images
endef
$(foreach img,$(HPPS_ZEBU_DDR_IMAGES_GEN),$(eval $(call hpps-zebu-ddr-imgage-rule,$(img))))

clean-hpps-zebu-ddr-images:
	rm -f $(HPPS_ZEBU_DDR_IMAGES) $(HPPS_ZEBU_DDR_IMAGES_BIN) $(HPPS_ZEBU_DDR_IMAGES_GEN)
.PHONY: clean-hpps-zebu-ddr-images

clean-hpps-zebu: clean-hpps-zebu-ddr-images
	rm -f $(HPPS_ZEBU_BIN)/mem.bin $(HPPS_ZEBU_BIN)/mem.dep
.PHONY: clean-hpps-zebu

%.vhex: %.bin
	$(TOOLS)/hpsc-objcopy -I binary -O Verilog-H $< $@
