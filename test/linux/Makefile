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

mboxtester.elf: mboxtester.c libmbox/libmbox.a
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) -Llibmbox -lmbox

%.elf: %.c
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

# %: %.elf doesn't match for some reason
define strip-rule
$(1): $(1).elf
	cp $$< $$@
	$(CROSS_COMPILE)$(STRIP) $$@
endef
$(foreach b,$(BINS),$(eval $(call strip-rule,$(b))))

clean: $(SUBDIRS)
	rm -rf *.o *.elf *.out $(BINS)

install: $(BINS)
	mkdir -p $(DEST)
	install $(BINS) $(DEST)
