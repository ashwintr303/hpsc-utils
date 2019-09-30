# Parse binary data in a given ftrace ramoops buffer image into text

$(call push-prof)

include $(CONF)/platform/Makefile
include $(CONF)/lib-trch-bm-preload-boot/Makefile
include $(CONF)/lib-trch-bm/Makefile
include $(CONF)/lib-hpps-linux-gpmem/Makefile
include $(CONF)/lib-hpps-ddr-high/Makefile

PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/qemu/env.sh: $(PROF_CONF)/qemu/env.sh
$(PROF_BLD)/qemu/preload.mem.map: $(PROF_CONF)/qemu/preload.mem.map
$(PROF_BLD)/hpps/initramfs.fs: $(PROF_CONF)/hpps/initramfs.dir
$(call dir-tree-rule,$(PROF_CONF)/hpps/initramfs.dir)
