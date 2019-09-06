TOPTARGETS := all clean

SUBDIRS := libmbox

CFLAGS += -Wall -Wextra -O1 -g -fstack-protector-strong -Wformat -Wformat-security

BINS = \
	mboxtester \
	mbox-multiple-core-tester \
	shm-standalone-tester \
	shm-tester \
	wdtester \
	rtit-tester \

.PHONY: $(TOPTARGETS) $(SUBDIRS)

all: $(SUBDIRS) $(BINS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

mboxtester: mboxtester.c mbox-utils.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) -Llibmbox -lmbox

mbox-multiple-core-tester: mbox-multiple-core-tester.c mbox-utils.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) -Llibmbox -lmbox

mbox-utils.o:	mbox-utils.c | libmbox
	$(CC) $(CFLAGS) -c -o $@ $< $(LDFLAGS) -Llibmbox -lmbox

%: %.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean: $(SUBDIRS)
	rm -rf *.o $(BINS)
