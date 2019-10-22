# Enable RTPS A53 CPU in Qemu machine model

$(call push-prof)
# includes
PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/qemu/hpsc.dtb: private CFLAGS+=-DCONFIG_RTPS_A53=1
