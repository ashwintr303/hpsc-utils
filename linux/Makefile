CC=aarch64-poky-linux-gcc
CFLAGS+=--sysroot=$(SYSROOT) -O1 -g

all: mboxtester wdtester

.PHONY: all

mboxtester: mboxtester.c
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ $^

wdtester: wdtester.c
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ $^

clean:
	rm -rf *.o mboxtester wdtester
