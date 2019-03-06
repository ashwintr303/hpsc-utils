RANLIB ?= ranlib
CFLAGS += -O1 -g

LIB = libmbox.a

all: $(LIB)

.PHONY: all

mbox.o: mbox.c
	$(CC) $(CFLAGS) -c $^ $(LDFLAGS)

$(LIB): mbox.o
	$(AR) rc $(LIB) mbox.o
	$(RANLIB) $(LIB)

clean:
	rm -rf *.o $(LIB)
