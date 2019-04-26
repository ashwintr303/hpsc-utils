#!/bin/bash

# This script perorms the parts of the initramfs creation that require fakeroot

# Create dirs here only because git can't hold empty dirs
mkdir -p dev proc

mknod dev/mem c 1 1
mknod dev/mtdblock0 b 31 0 # NAND
