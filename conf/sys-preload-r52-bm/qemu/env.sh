PROF_QEMU=$ROOT/$PROF_BLD/qemu
QEMU_DT_FILE=$PROF_QEMU/hpsc.dtb

PROF_TRCH=$ROOT/$PROF_BLD/trch

LSIO_SMC_SRAM_0+=(
    [src]=$ROOT/$PROF_BLD/trch/prof.sram.mem.bin
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
