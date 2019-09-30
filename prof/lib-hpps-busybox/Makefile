# Boot HPPS Linux into Busybox (from an initramfs archive).

$(call push-prof)

include $(CONF)/lib-hpps-linux-initramfs/Makefile

PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/hpps/busybox.miniconf: $(PROF_CONF)/hpps/busybox.miniconf

# We need to help the autodetector of module being built, because
# it can't see prerequisite lists, and the top-level target (initramfs.fs in
# this case) on its own doesn't imply which modules are prerequisites.
PROF_ARTS += $(PROF_BLD)/hpps/busybox/ $(PROF_BLD)/hpps/linux/

$(PROF_BLD)/hpps/initramfs.fs: \
	$(PROF_CONF)/hpps/initramfs.dir \
	$(PROF_CONF)/hpps/initramfs.dir.sh \
    $(PROF_BLD)/hpps/busybox/busybox.fr.dir \
	$(PROF_BLD)/hpps/linux/modules.fr.dir

$(call dir-tree-rule,$(PROF_CONF)/hpps/initramfs.dir)
