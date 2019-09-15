# QMP port set here for makefile to access it
# Value chosen disjoint with launch-qemu default and with other profiles
QMP_PORT=$((1024 + $(id -u) + 1))

GDB_PORT=none
SERIAL_ID="ftrace-extractor"
NET=none
