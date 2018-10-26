SYSROOTS=/path/to/pokysdk/sysroots/
SYSROOT=$(SYSROOTS)/aarch64-poky-linux
CROSS_COMPILE=$(SYSROOTS)/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-

mboxtester: mboxtester.c
	$(CROSS_COMPILE)gcc --sysroot=$(SYSROOT) -O1 -g $(INC) $(LIB) -o $@ $^

clean:
	rm -rf *.o mboxtester
