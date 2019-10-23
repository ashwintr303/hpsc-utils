# Enable Ethernet NIC of Synopsys DWC model in Qemu. Preload TRCH SSW
# Bare-Metal App binary (configured with minimal feature set) into TRCH SRAM,
# and ATF+U-boot+Linux binaries (configured for single-core boot -- not SMP)
# into HPPS DRAM by HW emulator (fast). Boot TRCH into TRCH SSW Bare-Metal App,
# boot HPPS into Busybox on Linux (configured with Synopsys DWC ethernet
# drivers and device tree nodes) via U-boot+ATF.

include $(CONF)/sys-preload-trch-bm-min-hpps-booti-linux-busybox/Makefile
include $(CONF)/lib-hpps-eth-snps/Makefile
