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

libmbox/libmbox.a:
	$(MAKE) -C $(@D) $(@F)

mboxtester: mboxtester.c libmbox/libmbox.a
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) -Llibmbox -lmbox

%: %.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean: $(SUBDIRS)
	rm -rf *.o $(BINS)
