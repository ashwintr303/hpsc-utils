# QMP port set here for makefile to access it, and for launch-qemu to
# get it from the environment.
# Value chosen disjoint with launch-qemu default and with other profiles

QMP_PORT=$((1024 + $(id -u) + 0))
GDB_PORT=none
SERIAL_ID="tool-nand-writer"
NET=none

HPPS_SMC_NAND_0[run]="$ROOT/$PROF_HOME/output.nand.bin"
