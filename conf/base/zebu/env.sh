PROF_DIR=$ROOT/bld/prof/$PROF
MEMORY_FILES+=($PROF_DIR/zebu/preload.mem.map)

# Parameters that depend on the hardware design of the HPSC Chiplet loaded into
# the Zebu emulator. Most of these are fixed, and not selectable at will.
# See conf/base/zebu/preload.mem.map for how to get mem size information.

# Note: With this base profile no source image is specified for any of the
# memory images, so by default blank images will be created. Profiles that wish
# to load the image from file, need to override the [src_file] property with
# the path to that file in the dictionaries below.

# HPPS SMC SRAM. All ranks are of equal size. Ranks and size is determined by
# the HW design loaded into the Zebu emulator and cannot be chosen at wil here.

HPPS_SMC_SRAM_PORTS=4

# All size values are in bytes, not bits
HPPS_SMC_SRAM_SIZE=16K
HPPS_SMC_SRAM_0+=( [size]=$HPPS_SMC_SRAM_SIZE )
HPPS_SMC_SRAM_1+=( [size]=$HPPS_SMC_SRAM_SIZE )
HPPS_SMC_SRAM_2+=( [size]=$HPPS_SMC_SRAM_SIZE )
HPPS_SMC_SRAM_3+=( [size]=$HPPS_SMC_SRAM_SIZE )


HPPS_SMC_NAND_PORTS=2

# These NAND layout parameters are not HW-dependent and can be chosen here.
# Also, we choose to apply these same values across all memory chips.
HPPS_SMC_NAND_PAGE_SIZE=2048 # bytes
HPPS_SMC_NAND_OOB_SIZE=64 # bytes
HPPS_SMC_NAND_ECC_SIZE=12 # bytes
HPPS_SMC_NAND_PAGES_PER_BLOCK=64 # bytes

# All size values are in bytes, not bits
HPPS_SMC_NAND_0+=(
    [size]=512M
    [page]=$HPPS_SMC_NAND_PAGE_SIZE
    [oob]=$HPPS_SMC_NAND_OOB_SIZE
    [ecc]=$HPPS_SMC_NAND_ECC_SIZE
    [ppb]=$HPPS_SMC_NAND_PAGES_PER_BLOCK
)
HPPS_SMC_NAND_1+=(
    [size]=32M
    [page]=$HPPS_SMC_NAND_PAGE_SIZE
    [oob]=$HPPS_SMC_NAND_OOB_SIZE
    [ecc]=$HPPS_SMC_NAND_ECC_SIZE
    [ppb]=$HPPS_SMC_NAND_PAGES_PER_BLOCK
)
