# Parameters that describe the target HW, necessary to execute the software
# stack on a target (emulator or real hardware, via the respective launch-*
# script), that are common across targets.

# Depending on the target, it may or may not be possible to change the
# HW characteristic by changing values here. For a SW emulator (like Qemu) that
# is able to instantiate different HW variant at will, changing values
# here (by overriding them in a profile or in a target specific env.sh)
# is ok; for other more rigid targets, the values here must match the
# characteristics of the actual HW design. The values here are the default
# across targets; if targets differ, then either (A) change the default to
# something supported by all targets, or (B) override variables defined here in
# the respective target's env.sh.

# Note: With this base profile no source image is specified for any of the
# memory images, so by default blank images will be created. Profiles that wish
# to load the image from file, need to override the [src_file] property with
# the path to that file in the dictionaries below.
#
# This src_file property does not belong here (unless the same file can and
# should be loaded by all targets in all configurations (profiles) --
# unlikely), nor in targets' env.sh (unless the same file should be loaded by
# the given target in all configurations -- unlikely), but in individual
# profiles (that have to do with storing something in the given NV memory).

# Memory connected to HPPS SMC SRAM ports

HPPS_SMC_SRAM_PORTS=4

# All size values are in bytes, not bits
HPPS_SMC_SRAM_SIZE=16K
HPPS_SMC_SRAM_0+=( [size]=$HPPS_SMC_SRAM_SIZE )
HPPS_SMC_SRAM_1+=( [size]=$HPPS_SMC_SRAM_SIZE )
HPPS_SMC_SRAM_2+=( [size]=$HPPS_SMC_SRAM_SIZE )
HPPS_SMC_SRAM_3+=( [size]=$HPPS_SMC_SRAM_SIZE )

# Memory connected to HPPS SMC NAND ports

HPPS_SMC_NAND_PORTS=2

# These NAND layout parameters are usually not HW-dependent and can be chosen
# here. Also, we choose to apply these same values across all memory chips.
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
