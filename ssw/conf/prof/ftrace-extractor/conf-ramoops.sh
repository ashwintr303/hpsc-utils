# These are used for dumping the buffer
RAMOOPS_CPU=4
RAMOOPS_ADDR=0x83200000
RAMOOPS_SIZE=0x400000
DUT_QMP_PORT=$((1024 + 1000 + $(id -u))) # run-qemu default for ID=0
