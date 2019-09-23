# Configuration for running on target platforms common across all profiles.
# This profile is somewhat special in that it is included automatically.

PROF_CONF:=$(CONF)/lib-platform

# Common across all platform platforms

# Qemu software emulator

$(PROF_BLD)/qemu: \
	$(PROF_BLD)/qemu/env.sh \
	$(PROF_BLD)/qemu/preload.mem.map \
	$(PROF_BLD)/qemu/hpsc.dtb ;

# TODO: platform.sh should move to the SDK (similar to how Qemu DT is in the SDK)
$(PROF_BLD)/qemu/env.sh: $(PROF_CONF)/platform.sh $(PROF_CONF)/qemu/env.sh \
						 | $(PROF_BLD)/qemu/

$(PROF_BLD)/qemu/hpsc.dts: $(QEMU_DT)/hpsc-arch.dts | $(PROF_BLD)/qemu/
$(PROF_BLD)/qemu/hpsc.dtb: $(PROF_BLD)/qemu/hpsc.dts
	$(call dtc-cmd,-I$(QEMU_DT))

# This profile introduces this file, so it's responsible for providing
# directory dep and a file to serve as merge base 
$(PROF_BLD)/qemu/preload.mem.map: $(PROF_CONF)/qemu/preload.mem.map \
				  | $(PROF_BLD)/qemu

# Synopsys FPGA-based Zebu emulator

ZEBU_ARTS += \
	$(PROF_BLD)/zebu/env.sh \
	$(PROF_BLD)/zebu/prof.hpps.dram.mem.raw \
# Add the following to also generate striped images (.bin or .vhex)
# $(PROF_BLD)/zebu/prof.hpps.ddr.x.bin

# For dependency extraction, need to add a mem.map (or derivative) to artifacts
PROF_ARTS += $(ZEBU_ARTS)

$(PROF_BLD)/zebu: $(ZEBU_ARTS) ;

# TODO: platform.sh should move to the SDK
$(PROF_BLD)/zebu/env.sh: $(PROF_CONF)/platform.sh $(PROF_CONF)/zebu/env.sh \
						 | $(PROF_BLD)/zebu/

$(PROF_BLD)/zebu/prof.hpps.conf.sh \
$(PROF_BLD)/zebu/prof.hpps.dram.mem.map \
: | $(PROF_BLD)/zebu/
