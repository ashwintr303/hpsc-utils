#!/bin/sh

set -e

function finish {
    [[ ! -f "$SIZE_FILE" ]] || rm -f $SIZE_FILE
}
trap finish EXIT

QMP_PORT=$1
shift
FTRACE_OUT=$1
shift

# No point passing via cmd line since this script is specific to this profile
source $CONF/lib-hpps-linux-gpmem/conf.sh
cpu=$HPPS_GPBUF_CPU
addr_gpmem=$HPPS_GPBUF_ADDR

# Must match init.d/10-parse-ramoops in this profile
addr_size=$(($addr_gpmem + 0x0000))
addr_data=$(($addr_gpmem + 0x1000))

SIZE_FILE=$(mktemp)

qmp-cmd localhost $QMP_PORT pmemsave \
    val=$addr_size size=32 filename="\"$(realpath $SIZE_FILE)\"" cpu-index=$cpu

SIZE="$(cat $SIZE_FILE)"
if [ -z "$SIZE" ]
then
    echo "ERROR: failed to get size of parsed ftrace data" 1>&2
    exit 1
fi

qmp-cmd localhost $QMP_PORT pmemsave \
    val=$addr_data size=$SIZE filename="\"$(realpath $FTRACE_OUT)\"" cpu-index=$cpu
