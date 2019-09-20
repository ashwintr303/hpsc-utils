include $(CONF)/lib-hpps-linux/Makefile

THIS_PROF:=lib-hpps-yocto
PROF_CONF:=$(CONF)/$(THIS_PROF)

$(PROF_BLD)/hpps/yocto.conf: $(PROF_CONF)/hpps/yocto.conf
$(PROF_BLD)/hpps/rootfs.fs: $(PROF_BLD)/hpps/prof.yocto.rootfs.tar.fr.dir
$(PROF_BLD)/qemu/env.sh: $(PROF_CONF)/qemu/env.sh

# Option for other profiles to share this profile's artifact by adding this
# profile name to the SHARE variable before including this makefile.
ifneq ($(call share,$(THIS_PROF),$(SHARE)),)
$(PROF_BLD)/hpps/prof.yocto.rootfs.tar.gz: \
	$(PROFDIR)/$(THIS_PROF)/$(BLDDIR)/hpps/yocto/yocto.rootfs.tar.gz
else # not share (build your own)

# Help out the used-module detector, since it can't see into prereqs
PROF_ARTS += $(PROF_BLD)/hpps/yocto/yocto.rootfs.tar.gz

$(PROF_BLD)/hpps/prof.yocto.rootfs.tar.gz: \
	$(PROF_BLD)/hpps/yocto/yocto.rootfs.tar.gz
endif

