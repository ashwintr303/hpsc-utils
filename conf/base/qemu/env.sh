PROF_DIR=$ROOT/bld/prof/$PROF

PROF_QEMU=$PROF_DIR/qemu
QEMU_DT_FILE=$PROF_QEMU/hpsc-arch.dtb
MEMORY_FILES+=($PROF_QEMU/preload.prof.mem.map)

PROF_TRCH=$PROF_DIR/trch

LSIO_SMC_SRAM_0+=(
    [src]=$PROF_TRCH/prof.sram.mem.bin
    [overwrite]=1
)

# Qemu Device Tree has a 2Gbit Numonyx MT29F2G08ABAEAWP NAND chip ID
HPPS_SMC_NAND_0[size]=256M

# Profiles may disable by setting the respective key to empty (unsetting the
# key instead of setting to empty applies the default in the launch-* script).
SERIAL_PORT_NAMES+=(
    [serial0]="trch"
    [serial1]=""
    [serial2]=""
)
