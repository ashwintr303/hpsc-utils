#!/bin/bash

# This script perorms the parts of the initramfs creation that require fakeroot

# Create dirs here only because git can't hold empty dirs
mkdir -p dev proc mnt/root

mknod dev/mem c 1 1
mknod dev/mtd0 c 90 0 # NAND
