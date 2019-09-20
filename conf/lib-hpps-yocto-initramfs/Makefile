# Boot HPPS Linux with full Yocto root file system as an initramfs image
# loaded into DRAM.

SHARE += lib-hpps-yocto

include $(CONF)/lib-hpps-yocto/Makefile
include $(CONF)/lib-hpps-linux-initramfs/Makefile

PROF_CONF=$(CONF)/lib-hpps-yocto-initramfs

$(PROF_BLD)/hpps/u-boot.env: $(PROF_CONF)/hpps/u-boot.env

$(PROF_BLD)/hpps/initramfs.fs: $(PROF_BLD)/hpps/prof.yocto.rootfs.tar.fr.dir
