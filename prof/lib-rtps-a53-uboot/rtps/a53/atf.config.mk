# DEBUG needs override, other vars shouldn't need it
override DEBUG:=1

# Top of RTPS DRAM partition that belongs to A53
HPSC_ATF_MEM_BASE=0x60000000
HPSC_ATF_MEM_SIZE=0x00020000
