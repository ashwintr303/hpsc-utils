# Configure RTPS R52 core 1 reset vector for U-boot

$(call push-prof)

include $(CONF)/lib-r52-uboot/Makefile

PROF_CONF:=$(CONF)/$(call pop-prof)

# TODO: RVBAR should be dynamically settable via TRCH
$(PROF_BLD)/qemu/hpsc.dts: $(PROF_CONF)/qemu/hpsc.dts
