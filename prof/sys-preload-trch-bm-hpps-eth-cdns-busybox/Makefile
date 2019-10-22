# Enable Ethernet NIC of Cadence MACB aka STMMAC model in Qemu machine model
# and enable drivers for it in HPPS Linux.  Preload TRCH SSW Bare-Metal App
# binary (configured with default feature set) into TRCH SRAM, and
# ATF+U-boot+Linux binaries into HPPS DRAM by HW emulator (fast). Boot TRCH
# into TRCH SSW Bare-Metal App, boot HPPS into Busybox on Linux via U-boot+ATF.

include $(CONF)/platform/Makefile
include $(CONF)/lib-preload-trch-bm/Makefile
include $(CONF)/lib-trch-bm-preload-boot/Makefile
include $(CONF)/lib-trch-bm-default/Makefile
include $(CONF)/lib-hpps-eth-cdns/Makefile
include $(CONF)/lib-hpps-busybox/Makefile
