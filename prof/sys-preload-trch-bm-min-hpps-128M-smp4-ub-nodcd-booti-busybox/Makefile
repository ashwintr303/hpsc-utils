# Preload TRCH SSW Bare-Metal App binary (configured with minimal feature set)
# into TRCH SRAM, and ATF+U-boot+Linux binaries (configured to boot on all 4
# cores of cluster 0 -- but not any cores of cluster 1) into HPPS DRAM by HW
# emulator (fast). Apply the workaround for the hang in U-boot in Dcache
# disable (do not disable). Boot TRCH into TRCH SSW Bare-Metal App, boot HPPS
# into Busybox on Linux via U-boot+ATF.

include $(CONF)/platform/Makefile
include $(CONF)/lib-preload-trch-bm/Makefile
include $(CONF)/lib-trch-bm-min/Makefile
include $(CONF)/lib-trch-bm-preload-boot/Makefile
include $(CONF)/lib-hpps-busybox/Makefile
include $(CONF)/lib-hpps-uboot-nodcd/Makefile
include $(CONF)/lib-hpps-linux-booti/Makefile
include $(CONF)/lib-hpps-linux-smp4/Makefile
