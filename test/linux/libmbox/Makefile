RANLIB ?= ranlib
CFLAGS += -O1 -g

LIB = libmbox.a

all: $(LIB)

.PHONY: all

mbox.o: mbox.c
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -c $^ $(LDFLAGS)

$(LIB): mbox.o
	$(CROSS_COMPILE)$(AR) rc $(LIB) mbox.o
	$(CROSS_COMPILE)$(RANLIB) $(LIB)

clean:
	rm -rf *.o $(LIB)
