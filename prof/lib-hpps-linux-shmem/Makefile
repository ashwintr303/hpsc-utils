# Enable HPSC Shared Memory regions between userspace in HPPS Linux and TRCH BM
# App

$(call push-prof)
# includes
PROF_CONF:=$(CONF)/$(call pop-prof)

$(PROF_BLD)/hpps/linux.config: $(PROF_CONF)/hpps/linux.config
$(PROF_BLD)/trch/bm.config.mk: $(PROF_CONF)/trch/bm.config.mk
$(PROF_BLD)/hpps/linux.dtb: private -DCONFIG_SHMEM=1
