# Load to top of TRCH SRAM, but leave space for syscfg to
# support the mode where syscfg is preloaded.
CONFIG_LOAD_ADDR=0x00000000
CONFIG_LOAD_SIZE=0x000ff000
