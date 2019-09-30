source $CONF/lib-hpps-linux-gpmem/conf.sh
source $CONF/tool-nand-writer/qemu/env.sh # To give makefile access to QMP_PORT

# Must match settings in initramfs/10-rootfs script from this profile
CPU=$HPPS_GPBUF_CPU
SIZE_ADDR=$(($HPPS_GPBUF_ADDR + 0x0000))
DONE_ADDR=$(($HPPS_GPBUF_ADDR + 0x0020))
DATA_ADDR=$(($HPPS_GPBUF_ADDR + 0x1000))
DONE_PATTERN="DONE"

