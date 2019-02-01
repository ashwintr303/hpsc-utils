TOPTARGETS := all clean

SUBDIRS := $(wildcard */.)

CFLAGS += -Wall -O1 -g

BINS = \
	mboxtester \
	shm-standalone-tester \
	wdtester \
	rtit-tester \

.PHONY: $(TOPTARGETS) $(SUBDIRS)

all: $(SUBDIRS) $(BINS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

mboxtester: mboxtester.c libmbox/libmbox.a
	$(CC) $(CFLAGS) -o $@ $@.c -Llibmbox -lmbox

%: %.c
	$(CC) $(CFLAGS) -o $@ $^

clean: $(SUBDIRS)
	rm -rf *.o $(BINS)
