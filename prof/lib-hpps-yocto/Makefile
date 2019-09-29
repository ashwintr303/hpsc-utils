# Boot Linux into Yocto root file system

$(call push-prof)

include $(CONF)/lib-hpps-linux/Makefile

THIS_PROF:=$(call pop-prof)
PROF_CONF:=$(CONF)/$(THIS_PROF)

$(PROF_BLD)/hpps/yocto-local.conf: $(PROF_CONF)/hpps/yocto-local.conf
$(PROF_BLD)/hpps/yocto-bblayers.conf: $(PROF_CONF)/hpps/yocto-bblayers.conf

$(PROF_BLD)/hpps/rootfs.fs: $(PROF_BLD)/hpps/prof.yocto.rootfs.tar.fr.dir
$(PROF_BLD)/qemu/env.sh: $(PROF_CONF)/qemu/env.sh

# Option for other profiles to share this profile's artifact by adding this
# profile name to the SHARE variable before including this makefile.
ifneq ($(call share,$(THIS_PROF),$(SHARE)),)
$(PROF_BLD)/hpps/prof.yocto.rootfs.tar.gz: \
	$(call share-art,$(THIS_PROF),hpps/yocto/yocto.rootfs.tar.gz)
else # not share (build your own)

# Need to add explicitly, so that when this profile is built on its own because
# it serves as a dependency of other profiles (without having any dependent
# artifacts picked up from the memory maps), this artifact gets built.
# Also, help out the used-module detector, since it can't see into prereqs.
PROF_ARTS += $(PROF_BLD)/hpps/yocto/yocto.rootfs.tar.gz

$(PROF_BLD)/hpps/prof.yocto.rootfs.tar.gz: \
	$(PROF_BLD)/hpps/yocto/yocto.rootfs.tar.gz
endif

