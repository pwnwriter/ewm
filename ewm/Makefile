LDFLAGS += -std=c99 -Wall -Wextra -pedantic -Wold-style-declaration
CFLAGS += -Wmissing-prototypes -Wno-unused-parameter
PREFIX ?= /usr
BINDIR ?= $(PREFIX)/bin
CC     ?= cc

all: ewm

config.h:
	cp config.def.h config.h

ewm: ewm.c ewm.h config.h Makefile
	$(CC) -O3 $(CFLAGS) -o $@ $< -lX11 $(LDFLAGS)

install: all
	install -Dm755 ewm $(DESTDIR)$(BINDIR)/ewm

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/ewm

clean:
	rm -f ewm *.o

.PHONY: all install uninstall clean
