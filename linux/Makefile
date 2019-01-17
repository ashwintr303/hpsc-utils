CFLAGS += -O1 -g

BINS = \
	mboxtester \
	wdtester \

all: $(BINS)

.PHONY: all

%: %.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf *.o $(BINS)
