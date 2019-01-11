CFLAGS += -O1 -g

all: mboxtester wdtester

.PHONY: all

mboxtester: mboxtester.c
	$(CC) $(CFLAGS) -o $@ $^

wdtester: wdtester.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf *.o mboxtester wdtester
