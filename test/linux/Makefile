export RANLIB ?= ranlib
export STRIP ?= strip

export CFLAGS += \
	-Wall -Wextra -Wformat -Wformat-security \
	-O1 -g \
	-fstack-protector-strong \
	-static \

TOPTARGETS := all clean

SUBDIRS := libmbox

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
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) -Llibmbox -lmbox

%: %.c
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean: $(SUBDIRS)
	rm -rf *.o $(BINS)

install: $(BINS)
	mkdir -p $(DEST)
	install $(BINS) $(DEST)
