# Boot Yocto Linux on HPPS with root file system mounted from NAND

SHARE += lib-hpps-yocto

include $(CONF)/lib-hpps-yocto/Makefile
include $(CONF)/lib-hpps-linux-nand/Makefile

THIS_PROF:=lib-hpps-yocto-nand

# Option for other profiles to share this profile's artifact by adding this
# profile name to the SHARE variable before including this makefile.
ifneq ($(call share,$(THIS_PROF),$(SHARE)),)
$(PROF_BLD)/hpps/prof.rootfs.nand.bin: \
	$(PROFDIR)/$(THIS_PROF)/$(BLDDIR)/hpps/rootfs.nand.bin
else # not share (build your own)
$(PROF_BLD)/hpps/prof.rootfs.nand.bin: $(PROF_BLD)/hpps/rootfs.nand.bin
endif
