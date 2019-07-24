# Write a tar.gz archive into image of NV mem at HPPS SMC353 NAND port

ifeq ($(filter %-clean,$(MAKECMDGOALS)),)
ifeq ($(ARCHIVE),)
$(error "ERROR: nand-writer profile requires ARCHIVE to be set")
endif
endif

include $(CONF_PROF)/dram-boot/Makefile
include $(CONF_PROF)/bm-minimal/Makefile
include $(CONF_PROF)/hpps-ddr-high/Makefile
include $(CONF_PROF)/hpps-linux-gpmem/Makefile

PROF_DIR=$(CONF_PROF)/nand-writer

$(BLD_PROF)/qemu/env.sh: $(PROF_DIR)/qemu/env.sh
$(BLD_PROF)/qemu/preload.prof.mem.map: $(PROF_DIR)/qemu/preload.prof.mem.map
$(BLD_PROF)/trch/syscfg.ini: $(PROF_DIR)/trch/syscfg.ini
$(BLD_PROF)/hpps/linux/initramfs.cpio: $(PROF_DIR)/hpps/linux/initramfs
