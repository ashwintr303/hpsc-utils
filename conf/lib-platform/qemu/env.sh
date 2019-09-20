QEMU_DT_FILE=($ROOT/$PROF_BLD/qemu/hpsc.dtb)
MEMORY_FILES+=($ROOT/$PROF_BLD/qemu/preload.mem.map)

# Hardware parameters. These don't belong in the launch-qemu script (or, in
# fact, in the SDK at all), because with respect to these parameters, the
# emulator (namely, Qemu) is fully flexible but the software stack is not.

# Qemu Device Tree has a 2Gbit Numonyx MT29F2G08ABAEAWP NAND chip ID
HPPS_SMC_NAND_0[size]=256M
