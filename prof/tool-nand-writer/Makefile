# Write a tar.gz archive into image of NV mem at HPPS SMC353 NAND port

$(call push-prof)

include $(CONF)/platform/Makefile
include $(CONF)/lib-trch-bm-preload-boot/Makefile
include $(CONF)/lib-trch-bm/Makefile
include $(CONF)/lib-hpps-busybox/Makefile
include $(CONF)/lib-hpps-ddr-high/Makefile
include $(CONF)/lib-hpps-linux-gpmem/Makefile

PROF_CONF:=$(CONF)/$(call pop-prof)

PROF_ARTS += $(PROF_HOME)/input.size

$(PROF_BLD)/preload.mem.map: $(PROF_CONF)/preload.mem.map
$(PROF_BLD)/qemu/env.sh: $(PROF_CONF)/qemu/env.sh

$(PROF_BLD)/trch/syscfg.ini: $(PROF_CONF)/trch/syscfg.ini
$(PROF_BLD)/trch/bm.config.mk: $(PROF_CONF)/trch/bm.config.mk

$(PROF_BLD)/hpps/initramfs.fs: $(PROF_CONF)/hpps/initramfs.dir
$(call dir-tree-rule,$(PROF_CONF)/hpps/initramfs.dir)

$(PROF_HOME)/%.size: $(PROF_HOME)/%.tar.gz
	stat -c '%32s' $< > $@

$(PROF_HOME)/input.tar.gz:
	@echo "ERROR: tool-nand-writer was not given input archive at path: $@" 2>&1
	exit 1
