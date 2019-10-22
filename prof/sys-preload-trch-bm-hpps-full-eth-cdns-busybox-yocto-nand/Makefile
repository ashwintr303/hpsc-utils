# Preload TRCH SSW Bare-Metal App binary (configured with default feature set)
# into TRCH on-chip SRAM and preload ATF+U-boot+Linux binaries (configured with
# default full feature set) into HPPS DRAM.  Boot TRCH into SSW BM App and have
# it boot HPPS into Linux into Busybox, whose init script then mounts root file
# system in NAND memory switch_roots into it.

include $(CONF)/platform/Makefile
include $(CONF)/lib-preload-trch-bm/Makefile
include $(CONF)/lib-trch-bm-preload-boot/Makefile
include $(CONF)/lib-trch-bm-default/Makefile
include $(CONF)/lib-hpps-full/Makefile
include $(CONF)/lib-hpps-eth-cdns/Makefile
SHARE += lib-hpps-yocto
include $(CONF)/lib-hpps-yocto/Makefile
include $(CONF)/lib-hpps-linux-nand-switchroot/Makefile
