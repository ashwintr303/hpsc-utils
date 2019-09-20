# Write a tar.gz archive into image of NV mem at HPPS SMC353 NAND port

include $(CONF)/sys-trch-bm/Makefile
include $(CONF)/lib-trch-bm-dram-boot/Makefile
include $(CONF)/lib-hpps-busybox/Makefile
include $(CONF)/lib-hpps-ddr-high/Makefile
include $(CONF)/lib-hpps-linux-gpmem/Makefile

PROF_ARTS += $(PROF_HOME)/input.size

PROF_CONF=$(CONF)/tool-nand-writer

$(PROF_BLD)/qemu/env.sh: $(PROF_CONF)/qemu/env.sh
$(PROF_BLD)/qemu/preload.mem.map: $(PROF_CONF)/qemu/preload.mem.map

$(PROF_BLD)/trch/syscfg.ini: $(PROF_CONF)/trch/syscfg.ini
$(PROF_BLD)/trch/bm.config.mk: $(PROF_CONF)/trch/bm.config.mk

$(PROF_BLD)/hpps/initramfs.fs: $(PROF_CONF)/hpps/initramfs.dir

$(PROF_HOME)/%.size: $(PROF_HOME)/%.tar.gz
	stat -c '%s' $< > $@ 

$(PROF_HOME)/input.tar.gz:
	@echo "ERROR: tool-nand-writer was not given input archive at path: $@" 2>&1
	exit 1
