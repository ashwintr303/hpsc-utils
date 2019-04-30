# Parse binary data in a given ftrace ramoops buffer image into text

ifeq ($(RAMOOPS),)
$(error "ERROR: ftrace-extractor profile requires RAMOOPS to be set")
endif

include $(CONF_PROF)/hpps-linux-gpmem/Makefile
include $(CONF_PROF)/hpps-ddr-high/Makefile

PROF_DIR=$(CONF_PROF)/ftrace-extractor

$(BLD_PROF)/qemu/preload.prof.mem.map: $(PROF_DIR)/qemu/preload.prof.mem.map
$(BLD_PROF)/hpps/linux/initramfs.cpio: $(PROF_DIR)/hpps/linux/initramfs
