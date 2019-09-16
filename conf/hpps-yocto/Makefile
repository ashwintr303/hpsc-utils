include $(CONF_PROF)/hpps-linux/Makefile

prof: $(BLD_PROF)/hpps/linux/yocto/conf/local.conf \
	$(BLD_PROF)/hpps/linux/yocto/conf/bblayers.conf \
	$(BLD_PROF)/hpps/linux/prof.yocto.rootfs.tar.gz

PROF_DIR=$(CONF_PROF)/hpps-yocto

$(BLD_PROF)/qemu/env.sh: $(PROF_DIR)/qemu/env.sh

# Share costly build artifact across profiles that include this profile
$(BLD_PROF)/hpps/linux/prof.yocto.rootfs.tar.gz: \
	$(BLD_PROFS)/hpps-yocto/hpps/linux/yocto.rootfs.tar.gz | $(BLD_PROF)/hpps/linux/
	cp -l $< $@
