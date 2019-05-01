source $CONF_PROF/hpps-linux-gpmem/conf.sh

# Must match settings in initramfs/10-rootfs script from this profile
DONE_CPU=4
DONE_ADDR=$(($HPPS_GPBUF_ADDR + 0x20))
DONE_PATTERN="DONE"

QMP_PORT=3024
