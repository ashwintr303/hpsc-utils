# Preload binaries into DRAM by HW emulator (fast), boot TRCH into bare-metal
# SSW app with minimal features enabled, boot HPPS into Busybox on Linux via
# ATF+U-boot's booti command (faster).

include $(CONF)/sys-preload-hpps-busybox/Makefile
include $(CONF)/lib-hpps-linux-booti/Makefile
include $(CONF)/lib-trch-bm-min/Makefile
