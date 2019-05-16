PROF_DIR=$(CONF_PROF)/hpps-linux-tests
OVERLAY_BLD_DIR=$(BLD_PROF)/hpps/linux/hpps-linux-tests

$(OVERLAY_BLD_DIR)/initramfs:
	$(MAKE) -C $(HPPS_LINUX_TESTS) DEST="$(abspath $@)/usr/bin/tests" install
.PHONY: $(OVERLAY_BLD_DIR)/initramfs

$(BLD_PROF)/hpps/linux/initramfs.cpio: $(OVERLAY_BLD_DIR)/initramfs
