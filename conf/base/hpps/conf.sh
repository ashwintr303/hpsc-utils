# Some params needed by the build but not part of any memory map file

HPPS_KERN_LOAD_ADDR=0x80680000 # (base + TEXT_OFFSET), where base must be aligned to 2MB
HPPS_UBOOT_ENV_SIZE=0x1000 # must match CONFIG_ENV_SIZE in u-boot config
