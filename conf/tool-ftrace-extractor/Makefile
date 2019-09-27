# Parse binary data in a given ftrace ramoops buffer image into text

include $(CONF)/lib-trch-bm-preload-boot/Makefile
include $(CONF)/lib-trch-bm/Makefile
include $(CONF)/lib-hpps-linux-gpmem/Makefile
include $(CONF)/lib-hpps-ddr-high/Makefile

PROF_CONF=$(CONF)/tool-ftrace-extractor

$(PROF_BLD)/qemu/env.sh: $(PROF_CONF)/qemu/env.sh
$(PROF_BLD)/qemu/preload.mem.map: $(PROF_CONF)/qemu/preload.mem.map
$(PROF_BLD)/hpps/initramfs.fs: $(PROF_CONF)/hpps/initramfs.dir
