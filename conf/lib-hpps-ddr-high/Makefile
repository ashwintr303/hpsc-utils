# [LIB] Add lots of DDR HI memory to HPPS subsystem
# Useful for infrastructure tasks to exchange data with the target.

$(call push-prof)
# includes
PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/qemu/hpsc.dts: $(PROF_CONF)/hpps-ddr-high-1.qemu.dts
$(PROF_BLD)/hpps/u-boot.dts: $(PROF_CONF)/hpps-ddr-high-1.uboot.dts
