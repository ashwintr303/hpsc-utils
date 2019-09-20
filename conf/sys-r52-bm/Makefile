# Boot TRCH into the SSW baremetal application, have TRCH load binaries from
# non-volatile memory and boot RTPS R52 into SSW bare-metal application via
# U-boot.

include $(CONF)/sys-trch-bm/Makefile
# include $(CONF)/lib-trch-bm-dram-boot/Makefile # preloaded works too
include $(CONF)/lib-trch-bm-nvmem-boot/Makefile
include $(CONF)/lib-r52-uboot-bm/Makefile
