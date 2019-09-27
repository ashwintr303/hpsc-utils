# [LIB] Boot HPPS Linux via U-boot's booti command

PROF_CONF=$(CONF)/lib-hpps-linux-booti

$(PROF_BLD)/hpps/u-boot.env: $(PROF_CONF)/hpps/u-boot.env

# One or the other will be used depending on TRCH boot configuration
# (see lib-trch-{nvmem,preload}-boot profiles).
$(PROF_BLD)/trch/boot.sfs.mem.map: $(PROF_CONF)/trch/boot.sfs.mem.map
$(PROF_BLD)/preload-boot.preload.mem.map: $(PROF_CONF)/preload-boot.preload.mem.map
