# Have TRCH boot subsystems without loading their binaries into DRAM,
# expecting that the binaries have been preloaded by the HW emulator.

PROF_CONF=$(CONF)/lib-trch-bm-dram-boot

PROF_ARTS += $(PROF_BLD)/qemu/preloadable.mem.map

$(PROF_BLD)/trch/syscfg.ini: $(PROF_CONF)/trch/syscfg.ini


# This profile introduces this file, so it's responsible for providing
# directory dep and a file to serve as merge base 
$(PROF_BLD)/qemu/preloadable.mem.map: $(PROF_CONF)/qemu/preloadable.mem.map \
				      | $(PROF_BLD)/qemu/

# If this profile was included, then preload what could be preloaded
$(PROF_BLD)/qemu/preload.mem.map: $(PROF_BLD)/qemu/preloadable.mem.map
