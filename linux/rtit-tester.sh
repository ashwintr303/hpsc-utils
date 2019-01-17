#!/bin/bash

set -e

INTERVAL_MS=2000
MASKS=(0x1 0x2 0x4 0x8 0x10 0x20 0x40 0x80)

for i in $(seq 0 7)
do
	taskset ${MASKS[$i]} ./rtit-tester /dev/rti_timer$i $INTERVAL_MS
done
