# QMP port set here for makefile to access it
# Value chosen disjoint with run-qemu default and with other profiles
QMP_PORT=$((1024 + $(id -u) + 0))

GDB_PORT=none
SERIAL_ID="nand-writer"
NET=none
