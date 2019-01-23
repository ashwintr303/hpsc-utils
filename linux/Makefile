CFLAGS += -O1 -g

BINS = \
	mboxtester \
	shmtester \
	wdtester \
	rtit-tester \

all: $(BINS)

.PHONY: all

%: %.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf *.o $(BINS)
