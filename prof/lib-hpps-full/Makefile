# Enable all HW IP blocks in HPPS subsystem in Qemu machine configuration.

# Note: these will configure HPPS Linux, but not include Linux as an artifact,
# so it is safe to include from profiles that don't run Linux, but just want
# the full HPPS HW configuration. Configuring a component does not pull it into
# the build/run.

include $(CONF)/lib-hpps-a53/Makefile
include $(CONF)/lib-hpps-pmu/Makefile
include $(CONF)/lib-hpps-smmu/Makefile
include $(CONF)/lib-hpps-wdt/Makefile
include $(CONF)/lib-hpps-rti/Makefile
include $(CONF)/lib-hpps-dma/Makefile
include $(CONF)/lib-hpps-smc/Makefile
include $(CONF)/lib-hpps-linux-msg-mbox/Makefile
include $(CONF)/lib-hpps-linux-msg-shmem/Makefile
include $(CONF)/lib-hpps-linux-shmem/Makefile
include $(CONF)/lib-hpps-linux-mbox/Makefile
