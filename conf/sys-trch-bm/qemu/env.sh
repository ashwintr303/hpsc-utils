LSIO_SMC_SRAM_0+=(
    [src]=$ROOT/$PROF_BLD/trch/prof.sram.mem.bin
    [overwrite]=1
)

# Profiles may disable by setting the respective key to empty (unsetting the
# key instead of setting to empty applies the default in the launch-* script).
SERIAL_PORT_NAMES+=(
    [serial0]="trch"
    [serial1]=""
    [serial2]=""
)
