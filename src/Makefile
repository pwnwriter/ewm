CFLAGS += -std=c99 -Wall -Wextra -pedantic -Wold-style-declaration
CFLAGS += -Wmissing-prototypes -Wno-unused-parameter
PREFIX ?= /usr
BINDIR ?= $(PREFIX)/bin
CC     ?= gcc

all: ewm

config.h:
	cp config.def.h config.h

ewm: ewm.c ewm.h config.h Makefile
	$(CC) -O3 $(CFLAGS) -o $@ $< -lX11 $(LDFLAGS)

install: all
	install -Dm755 ewm $(DESTDIR)$(BINDIR)/ewm
	install -Dm755 swpb $(DESTDIR)$(BINDIR)/swpb

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/ewm
	rm -f $(DESTDIR)$(BINDIR)/swpb

clean:
	rm -f ewm *.o
	rm -rf config.h

.PHONY: all install uninstall clean
