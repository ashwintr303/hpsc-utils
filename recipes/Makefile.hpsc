# Relative paths to reduce duplication throughout this file
QEMU=qemu
QEMU_DT=qemu-devicetrees
HPSC_UTILS=hpsc-utils
TOOLS=$(HPSC_UTILS)/host
CONF=$(HPSC_UTILS)/conf
HPPS_UTILS=$(HPSC_UTILS)/hpps
HPPS_INITRAMFS=$(HPPS_UTILS)/initramfs
HPPS_ZEBU=$(CONF)/zebu/hpps
HPPS_CONF=$(CONF)/hpps
HPPS_BUSYBOX_CONF=$(HPPS_CONF)/busybox
DT_OL=$(CONF)/dt
DT_OL_QEMU=$(DT_OL)/qemu
DT_OL_LINUX=$(DT_OL)/linux
DT_OL_UBOOT=$(DT_OL)/uboot
HPPS=hpps
RTPS=rtps
RTPS_R52=$(RTPS)/r52
RTPS_A53=$(RTPS)/a53
HPPS_ATF=$(HPPS)/arm-trusted-firmware
HPPS_UBOOT=$(HPPS)/u-boot
HPPS_LINUX=$(HPPS)/linux
HPPS_LINUX_BOOT=$(HPPS_LINUX)/arch/arm64/boot
HPPS_BUSYBOX=$(HPPS)/userspace/busybox
RTPS_R52_UBOOT=$(RTPS_R52)/u-boot
RTPS_A53_UBOOT=$(RTPS_A53)/u-boot
RTPS_A53_ATF=$(RTPS_A53)/arm-trusted-firmware
BARE_METAL=hpsc-baremetal
# Directory for artifacts created by this top-level build
BIN=bin
HPPS_BIN=$(BIN)/hpps
HPPS_ZEBU_BIN=$(HPPS_BIN)/zebu
QEMU_BLD=$(BIN)/qemu-bld

# Profiles
HPPS_DEFAULT=$(HPPS_BIN)/default
HPPS_FTRACE_EXT=$(HPPS_BIN)/ftrace-extractor

HPPS_DEFAULT_INITRAMFS=$(HPPS_DEFAULT)/initramfs
HPPS_FTRACE_EXT_INITRAMFS=$(HPPS_FTRACE_EXT)/initramfs

CROSS_A53=aarch64-poky-linux-
CROSS_A53_LINUX=aarch64-linux-gnu-
CROSS_R52=arm-none-eabi-
CROSS_M4=arm-none-eabi-

# Settings for build artifacts produced by this top-level builder
HPPS_KERN_LOAD_ADDR=0x8068_0000 # (base + TEXT_OFFSET), where base must be aligned to 2MB
HPPS_DRAM_ADDR=0x8000_0000

# Build Qemu s.t. its GDB stub points to the given target CPU cluster:
# TRCH=0, RTPS_R52=1, RTPS_A53=2, HPPS=3
QEMU_GDB_TARGET_CLUSTER=3

HPPS_ZEBU_DDR_IMAGES=$(HPPS_ZEBU_BIN)/ddr0.bin $(HPPS_ZEBU_BIN)/ddr1.bin

# Address parsing function, takes addresses with _ separators
addr=$(subst _,,$1)

# Shortcut aliases
#
# Note: all clean targets here are hardest cleans, and all builds are full,
# e.g. including regeneration of config, if you want any other clean or partial
# build, then use the build system of the respective component directly.

all: qemu qdt target
clean: clean-qemu clean-qdt clean-target

target: trch rtps hpps
clean-target: clean-trch clean-rtps clean-hpps
.PHONY: target clean-target

trch: trch-bm
clean-trch: clean-trch-bm
.PHONY: trch clean-trch

rtps: rtps-r52 rtps-a53
clean-rtps: clean-rtps-r52 clean-rtps-a53
.PHONY: rtps clean-rtps

hpps: hpps-atf hpps-uboot hpps-linux hpps-initramfs
clean-hpps: clean-hpps-atf clean-hpps-uboot clean-hpps-linux \
	clean-hpps-busybox clean-hpps-initramfs
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

QEMU_ARGS=-C $(QEMU_BLD) CFLAGS+=-DGDB_TARGET_CLUSTER=$(QEMU_GDB_TARGET_CLUSTER)
$(QEMU_BLD)/aarch64-softmmu/qemu-system-aarch64: qemu

$(QEMU_BLD)/config.status: | $(QEMU_BLD)/
	cd $(QEMU_BLD) && ../../$(QEMU)/configure \
		--target-list=aarch64-softmmu --enable-fdt \
		--disable-kvm --disable-xen --enable-debug
qemu: $(QEMU_BLD)/config.status
	$(MAKE) $(QEMU_ARGS)
clean-qemu:
	$(MAKE) $(QEMU_ARGS) clean
.PHONY: qemu clean-qemu

QDT_ARGS=-C $(QEMU_DT)
$(QEMU_DT)/LATEST/SINGLE_ARCH/hpsc-arch.dtb: qdt
qdt:
	$(MAKE) $(QDT_ARGS)
clean-qdt:
	$(MAKE) $(QDT_ARGS) clean
.PHONY: qdt clean-qdt

TRCH_BM_ARGS=-C $(BARE_METAL)/trch
$(BARE_METAL)/trch/bld/trch.elf: trch-bm
trch-bm:
	$(MAKE) $(TRCH_BM_ARGS) CROSS_COMPILE=$(CROSS_M4)
clean-trch-bm:
	$(MAKE) $(TRCH_BM_ARGS) clean
.PHONY: trch-bm clean-trch-bm

RTPS_R52_BM_ARGS=-C $(BARE_METAL)/rtps
$(BARE_METAL)/rtps/bld/rtps.uimg: rtps-bm
rtps-r52-bm:
	$(MAKE) $(RTPS_R52_BM_ARGS) CROSS_COMPILE=$(CROSS_R52)
clean-rtps-r52-bm:
	$(MAKE) $(RTPS_R52_BM_ARGS) clean
.PHONY: rtps-r52-bm clean-rtps-r52-bm

RTPS_R52_UBOOT_MAKE_ARGS=-C $(RTPS_R52_UBOOT) CROSS_COMPILE=$(CROSS_R52)
$(RTPS_R52_UBOOT)/.config: $(RTPS_R52_UBOOT)/configs/hpsc_rtps_r52_defconfig
	$(MAKE) $(RTPS_R52_UBOOT_MAKE_ARGS) hpsc_rtps_r52_defconfig
$(RTPS_R52_UBOOT)/u-boot.bin: rtps-r52-uboot
rtps-r52-uboot: $(RTPS_R52_UBOOT)/.config
	$(MAKE) $(RTPS_R52_UBOOT_MAKE_ARGS) u-boot.bin
clean-rtps-r52-uboot:
	$(MAKE) $(RTPS_R52_UBOOT_MAKE_ARGS) clean
	rm -f $(RTPS_R52_UBOOT)/.config
.PHONY: rtps-r52-uboot clean-rtps-r52-uboot

RTPS_A53_UBOOT_MAKE_ARGS=-C $(RTPS_A53_UBOOT) CROSS_COMPILE=$(CROSS_A53)
$(RTPS_A53_UBOOT)/.config: $(RTPS_A53_UBOOT)/configs/hpsc_rtps_a53_defconfig
	$(MAKE) $(RTPS_A53_UBOOT_MAKE_ARGS) hpsc_rtps_a53_defconfig
$(RTPS_A53_UBOOT)/u-boot.bin: rtps-a53-uboot
rtps-a53-uboot: $(RTPS_A53_UBOOT)/u-boot.bin
	$(MAKE) $(RTPS_A53_UBOOT_MAKE_ARGS) u-boot.bin
clean-rtps-a53-uboot:
	$(MAKE) $(RTPS_A53_UBOOT_MAKE_ARGS) clean
	rm -f $(RTPS_A53_UBOOT)/.config
.PHONY: rtps-a53-uboot clean-rtps-a53-uboot

RTPS_A53_ATF_MAKE_ARGS=-C $(RTPS_A53_ATF) \
	PLAT=hpsc_rtps_a53 DEBUG=1 CROSS_COMPILE=$(CROSS_A53)
$(RTPS_A53_ATF)/build/hpsc_rtps_a53/debug/bl31.bin: rtps-a53-atf
rtps-a53-atf:
	$(MAKE) $(RTPS_A53_ATF_MAKE_ARGS) bl31
clean-rtps-a53-atf:
	$(MAKE) $(RTPS_A53_ATF_MAKE_ARGS) clean
.PHONY: rtps-a53-atf clean-rtps-a53-atf

HPPS_ATF_MAKE_ARGS=-C $(HPPS_ATF) PLAT=hpsc DEBUG=1 CROSS_COMPILE=$(CROSS_A53)
$(HPPS_ATF)/build/hpsc/debug/bl31.bin: hpps-atf
hpps-atf:
	$(MAKE) $(HPPS_ATF_MAKE_ARGS) bl31
clean-hpps-atf:
	$(MAKE) $(HPPS_ATF_MAKE_ARGS) clean
.PHONY: hpps-atf clean-hpps-atf

HPPS_UBOOT_MAKE_ARGS=-C $(HPPS_UBOOT) CROSS_COMPILE=$(CROSS_A53)
$(HPPS_UBOOT)/.config: $(HPPS_UBOOT)/configs/hpsc_hpps_defconfig
	$(MAKE) $(HPPS_UBOOT_MAKE_ARGS) hpsc_hpps_defconfig
$(HPPS_UBOOT)/u-boot.bin: hpps-uboot
hpps-uboot: $(HPPS_UBOOT)/.config
	$(MAKE) $(HPPS_UBOOT_MAKE_ARGS) u-boot.bin
clean-hpps-uboot:
	$(MAKE) $(HPPS_UBOOT_MAKE_ARGS) clean
	rm -f $(HPPS_UBOOT)/.config
.PHONY: hpps-uboot clean-hpps-uboot

HPPS_LINUX_MAKE_ARGS=-C $(HPPS_LINUX) ARCH=arm64 CROSS_COMPILE=$(CROSS_A53)
$(HPPS_LINUX)/.config: $(HPPS_LINUX)/arch/arm64/configs/hpsc_defconfig
	$(MAKE) $(HPPS_LINUX_MAKE_ARGS) hpsc_defconfig

$(HPPS_LINUX_BOOT)/Image.gz: $(HPPS_LINUX)/.config
	$(MAKE) $(HPPS_LINUX_MAKE_ARGS) Image.gz

# Note: need to sequence, otherwise whether we have two targets at same
# priority or we have one recipe with multiple artifacts, in both cases will be
# broken with parallel make. We do want explicit references to both artifacts
# in this makefile though, because they both participate in images.
$(HPPS_LINUX_BOOT)/dts/hpsc/hpsc.dtb: $(HPPS_LINUX_BOOT)/Image.gz
	$(MAKE) $(HPPS_LINUX_MAKE_ARGS) hpsc/hpsc.dtb

$(HPPS_BIN)/uImage: $(HPPS_LINUX_BOOT)/Image.gz | $(HPPS_BIN)/
	mkimage -T kernel -C gzip -A arm64 -d "$<" -a $(call addr,${HPPS_KERN_LOAD_ADDR}) "$@"

# The make command in this recipe is only used for the invocation from the user
# interface (via hpps-linux phony target shortcut), but not from the dependency
# build of another artifact, for which the above recipes are used (a violation
# of the invariant above). We could eliminate this by adding phony targets for
# Image.gz and hpsc.dtb and have hpps-linux target and the non-phony
# targets for Image.gz, hpsc.dtb artifacts depend on those phony targets. Meh.
hpps-linux: $(HPPS_LINUX)/.config
	$(MAKE) $(HPPS_LINUX_MAKE_ARGS)
	$(MAKE) $(HPPS_BIN)/uImage
clean-hpps-linux:
	$(MAKE) $(HPPS_LINUX_MAKE_ARGS) mrproper
	rm -f $(HPPS_BIN)/uImage
.PHONY: hpps-linux clean-hpps-linux


HPPS_BUSYBOX_ARGS=-C $(HPPS_BUSYBOX) CROSS_COMPILE=$(CROSS_A53_LINUX) \
		CONFIG_PREFIX="$(abspath $(HPPS_DEFAULT_INITRAMFS))"
$(HPPS_BUSYBOX)/.config: $(HPPS_BUSYBOX_CONF)/hpsc_hpps_miniconf
	$(MAKE) $(HPPS_BUSYBOX_ARGS) allnoconfig KCONFIG_ALLCONFIG="$(abspath $<)"
$(HPPS_BUSYBOX)/busybox: hpps-busybox
hpps-busybox: $(HPPS_BUSYBOX)/.config
	$(MAKE) $(HPPS_BUSYBOX_ARGS)
clean-hpps-busybox:
	$(MAKE) $(HPPS_BUSYBOX_ARGS) clean
	rm -f $(HPPS_BUSYBOX)/.config
.PHONY: hpps-busybox clean-hpps-busybox

HPPS_FAKEROOT_ENV=$(abspath $(HPPS_BIN)/initramfs.fakeroot)
$(HPPS_DEFAULT)/initramfs.cpio: | $(HPPS_DEFAULT)/
	rsync -aq $(HPPS_INITRAMFS)/ $(HPPS_DEFAULT_INITRAMFS)
	$(call make-initramfs,$(HPPS_DEFAULT_INITRAMFS),$(HPPS_FAKEROOT_ENV))
	cd $(HPPS_DEFAULT_INITRAMFS) && $(call make-cpio,$(HPPS_FAKEROOT_ENV))

# args: dest, fakeroot_env
define make-initramfs
cd $(1) && fakeroot -i $(2) -s $(2) $(abspath $(HPPS_UTILS))/initramfs.sh
fakeroot -i $(2) -s $(2) $(MAKE) $(HPPS_BUSYBOX_ARGS) install
endef

# args: fakeroot_env
define make-cpio
find . | fakeroot -i $(1) -s $(1) cpio -R root:root -c -o -O "$(abspath $@)"
endef

$(HPPS_BIN)/%/initramfs.uimg: $(HPPS_BIN)/%/initramfs.cpio.gz
	mkimage -T ramdisk -C gzip -A arm64 -n "Initramfs" -d "$<" "$@"

hpps-initramfs: hpps-busybox
	$(MAKE) $(HPPS_DEFAULT)/initramfs.uimg
clean-hpps-initramfs:
	rm -rf $(HPPS_DEFAULT)/initramfs.{uimg,cpio,cpio.gz} $(HPPS_DEFAULT_INITRAMFS)
.PHONY: hpps-initramfs clean-hpps-initramfs

# The following targets define profiles
# TODO: explain
# TODO: profile subdir

$(HPPS_FTRACE_EXT)/fx.hpsc.qemu.dts: \
	$(QEMU_DT)/hpsc-arch.dts \
	$(DT_OL_QEMU)/hpps-ddr-high-1.dts

$(HPPS_FTRACE_EXT)/fx.hpps.uboot.dts: \
	$(HPPS_UBOOT)/arch/arm/dts/hpsc-hpps.dts \
	$(DT_OL_UBOOT)/hpps-ddr-high-1.dts

$(HPPS_FTRACE_EXT)/fx.hpps.linux.dts: \
	$(HPPS_LINUX_BOOT)/dts/hpsc/hpsc.dts \
	$(DT_OL_LINUX)/gp-mem.dts

# TODO: make generic
$(HPPS_FTRACE_EXT)/%.dts:
	cat $^ > $@

# TODO: possible to make u-boot target generic across all profiles?

# U-boot's DT is merged into u-boot.bin image (and that merge is non-trivial),
# so have to build the whole thing. Use rsync to approximate an out-of-tree build.
$(HPPS_FTRACE_EXT)/$(HPPS_UBOOT)/u-boot.bin: $(HPPS_FTRACE_EXT)/fx.hpps.uboot.dts \
						| $(HPPS_FTRACE_EXT)/$(HPPS)/
	rsync -aq $(foreach ext,o a bin sym elf cfg dtb dtb.S mk.dep,--exclude='*.$(ext)') \
		$(HPPS_UBOOT) $(HPPS_FTRACE_EXT)/$(HPPS)/
	cp $(HPPS_FTRACE_EXT)/fx.hpps.uboot.dts \
		$(HPPS_FTRACE_EXT)/$(HPPS_UBOOT)/arch/arm/dts/hpsc-hpps.dts
	cd $(HPPS_FTRACE_EXT) && $(MAKE) $(HPPS_UBOOT_MAKE_ARGS)

$(HPPS_FTRACE_EXT)/initramfs.cpio: $(HPPS_DEFAULT)/initramfs.cpio | $(HPPS_FTRACE_EXT)/
	fakeroot -i $(HPPS_FAKEROOT_ENV) -s $(HPPS_FAKEROOT_ENV) \
		cp -r $(HPPS_DEFAULT_INITRAMFS) $(HPPS_FTRACE_EXT)/
	cd $(HPPS_FTRACE_EXT_INITRAMFS) && \
		fakeroot -i $(HPPS_FAKEROOT_ENV) -s $(HPPS_FAKEROOT_ENV) \
			ln -sf init-extract-ftrace init
	cd $(HPPS_FTRACE_EXT_INITRAMFS)/ && find . | \
		fakeroot -i $(HPPS_FAKEROOT_ENV) -s $(HPPS_FAKEROOT_ENV) \
			cpio -R root:root -c -o -O "$(abspath $@)"

ftrace-extractor: $(HPPS_FTRACE_EXT)/ \
	$(HPPS_FTRACE_EXT)/initramfs.uimg \
	$(HPPS_FTRACE_EXT)/fx.hpps.linux.dtb \
	$(HPPS_FTRACE_EXT)/fx.hpsc.qemu.dtb \
	$(HPPS_FTRACE_EXT)/$(HPPS_UBOOT)/u-boot.bin
clean-ftrace-extractor:
	rm -rf $(HPPS_FTRACE_EXT)/
.PHONY: ftrace-extractor clean-ftrace-extractor

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

%.gz: %
	gzip -c -9 "$<" > "$@"

%.qemu.dtb: %.qemu.dts
	$(call dt-rule,-I$(QEMU_DT))

%.hpps.uboot.dtb: %.hpps.uboot.dts
	$(call dt-rule,-I$(HPPS_UBOOT)/arch/arm/dts)

%.hpps.linux.dtb: %.hpps.linux.dts
	$(call dt-rule,-I$(HPPS_LINUX)/include -I$(HPPS_LINUX_BOOT)/dts/hpsc)

%.dtb: %.dts
	$(call dt-rule,)

define dt-rule
	$(CC) -E -nostdinc -x assembler-with-cpp $(1) -o - $< | \
		dtc -q -I dts -O dtb -o $@ -
endef
