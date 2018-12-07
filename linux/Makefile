SYSROOTS=/opt/poky/2.3.4/sysroots
SYSROOT=$(SYSROOTS)/aarch64-poky-linux
CROSS_COMPILE=$(SYSROOTS)/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-

all: mboxtester wdtester

.PHONY: all

mboxtester: mboxtester.c
	$(CROSS_COMPILE)gcc --sysroot=$(SYSROOT) -O1 -g $(INC) $(LIB) -o $@ $^

wdtester: wdtester.c
	$(CROSS_COMPILE)gcc --sysroot=$(SYSROOT) -O1 -g $(INC) $(LIB) -o $@ $^

clean:
	rm -rf *.o mboxtester wdtester
