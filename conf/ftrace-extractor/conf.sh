source $CONF_PROF/nand-writer/qemu/env.sh
source $CONF_PROF/hpps-linux-gpmem/conf.sh

# Must match settings in initramfs/10-parse-ramoops script from this profile
DONE_CPU=$HPPS_GPBUF_CPU
DONE_ADDR=$(($HPPS_GPBUF_ADDR + 0x20))
DONE_PATTERN="DONE"
