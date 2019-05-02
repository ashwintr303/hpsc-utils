TOPTARGETS := all clean

SUBDIRS := libmbox

CFLAGS += -Wall -Wextra -O1 -g -fstack-protector-strong -Wformat -Wformat-security

BINS = \
	mboxtester \
	shm-standalone-tester \
	shm-tester \
	wdtester \
	rtit-tester \

.PHONY: $(TOPTARGETS) $(SUBDIRS)

all: $(SUBDIRS) $(BINS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

mboxtester: mboxtester.c | libmbox
	$(CC) $(CFLAGS) -o $@ $@.c $(LDFLAGS) -Llibmbox -lmbox

%: %.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean: $(SUBDIRS)
	rm -rf *.o $(BINS)
