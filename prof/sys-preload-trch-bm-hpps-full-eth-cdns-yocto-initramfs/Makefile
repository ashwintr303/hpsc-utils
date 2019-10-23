# Enable all HPPS HW blocks (including Ethernet NIC of Cadence MACB aka STMMAC
# model) in Qemu machine model and enable drivers for them in HPPS Linux.
# Preload TRCH SSW Bare-Metal App binary (configured with default feature set)
# into TRCH on-chip SRAM and preload ATF+U-boot+Linux binaries (configured with
# default full feature set) and initramfs image with Yocto root file system
# into HPPS DRAM.  Boot TRCH into SSW BM App and have it boot HPPS into Yocto
# Linux.
# DEPENDS (must be built beforehand): lib-hpps-yocto

include $(CONF)/platform/Makefile
include $(CONF)/lib-preload-trch-bm/Makefile
include $(CONF)/lib-trch-bm-preload-boot/Makefile
include $(CONF)/lib-trch-bm-default/Makefile
SHARE += lib-hpps-yocto
include $(CONF)/lib-hpps-yocto-initramfs/Makefile
include $(CONF)/lib-hpps-full/Makefile
include $(CONF)/lib-hpps-eth-cdns/Makefile
