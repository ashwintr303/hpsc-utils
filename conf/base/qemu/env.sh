PROF_DIR=$ROOT/bld/prof/$PROF

PROF_QEMU=$PROF_DIR/qemu
QEMU_DT_FILE=$PROF_QEMU/hpsc-arch.dtb
MEMORY_FILES+=($PROF_QEMU/preload.prof.mem.map)

PROF_TRCH=$PROF_DIR/trch

LSIO_SMC_SRAM_0+=(
    [src]=$PROF_TRCH/prof.sram.mem.bin
    [overwrite]=1
)

SERIAL_PORT_NAMES+=(
    [serial0]="trch"
    [serial1]="rtps-r52"
    [serial2]="hpps"
)
