# Preload BL0 ROM bootloader into TRCH SRAM (by emulator), and have BL0 load
# TRCH SSW bare-metal application (configurd with tests to run on boot) from
# offchip non-volatile memory, and boot into it and run the tests.

include $(CONF)/platform/Makefile
include $(CONF)/lib-bl0-trch-bm/Makefile
include $(CONF)/lib-trch-bm-nvmem-boot/Makefile
include $(CONF)/lib-trch-bm-test/Makefile
