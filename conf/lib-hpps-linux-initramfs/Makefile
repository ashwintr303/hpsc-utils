# Configure HPPS Linux to boot into an initramfs image (a cpio archive).

include $(CONF)/lib-hpps-linux/Makefile

PROF_CONF=$(CONF)/lib-hpps-linux-initramfs

$(PROF_BLD)/hpps/u-boot.env: $(PROF_CONF)/hpps/u-boot.env

$(PROF_BLD)/trch/boot.sfs.mem.map: $(PROF_CONF)/trch/boot.sfs.mem.map
$(PROF_BLD)/preload-boot.preload.mem.map: $(PROF_CONF)/preload-boot.preload.mem.map
