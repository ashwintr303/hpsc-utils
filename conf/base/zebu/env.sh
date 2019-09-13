PROF_DIR=$ROOT/bld/prof/$PROF
MEMORY_FILES+=($PROF_DIR/zebu/preload.mem.map)

# Parameters that depend on the hardware design of the HPSC Chiplet loaded into
# the Zebu emulator. Most of these are fixed, and not selectable at will.

HPPS_SRAM_SIZE=0x01000000 #  16MB

HPPS_NAND_SIZE=0x20000000 # 512 MB (4 Gbit chip)
HPPS_NAND_PAGE_SIZE=2048 # bytes
HPPS_NAND_OOB_SIZE=64 # bytes
HPPS_NAND_ECC_SIZE=12 # bytes
HPPS_NAND_PAGES_PER_BLOCK=64 # bytes

