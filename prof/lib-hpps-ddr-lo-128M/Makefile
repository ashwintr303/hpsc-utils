# Configure HPPS DDR LO size to 128 MiB (zero for DDR HI)
# in Qemu machine model and U-boot/Linux device tree.

$(call push-prof)
# includes
PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/hpps/u-boot.dts: $(PROF_CONF)/hpps/u-boot.dts

$(PROF_BLD)/qemu/hpsc.cpp.dts: private CFLAGS+=\
	-DCONFIG_HPPS_DDR_LO_SIZE=0x08000000  \
	-DCONFIG_HPPS_DDR_HI_SIZE_HI=0
