#!/bin/bash

set -e

MASKS=(0x1 0x2 0x4 0x8 0x10 0x20 0x40 0x80)

while true
do
	for i in $(seq 0 7)
	do
		taskset ${MASKS[$i]} bash -c "echo 1 > /dev/watchdog$i"
	done
	sleep 2
done
