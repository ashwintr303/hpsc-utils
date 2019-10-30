# Some params needed by the build but not part of any memory map file

KERN_LOAD_ADDR=0x81a80000 # (base + TEXT_OFFSET), where base must be aligned to 2MB
UBOOT_ENV_SIZE=0x1000 # must match CONFIG_ENV_SIZE in u-boot config
