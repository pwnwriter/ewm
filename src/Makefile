LDFLAGS += -std=c99 -Wall -Wextra -pedantic -Wold-style-declaration
CFLAGS 	+= -Wmissing-prototypes -Wno-unused-parameter
PREFIX 	?= /usr
BINDIR 	?= $(PREFIX)/bin
MANDIR	?= $(PREFIX)/share/man/man1
CC     	?= gcc

all: ewm

config.h:
	cp config.def.h config.h

ewm: ewm.c ewm.h config.h Makefile
	$(CC) -O3 $(CFLAGS) -o ewm ewm.c -lX11 -lXext $(LDFLAGS)

install: all
	install -Dm755 ewm $(DESTDIR)$(BINDIR)/ewm
	install -Dm755 swpb $(DESTDIR)$(BINDIR)/swpb
	install -Dm644 ewm.1 $(DESTDIR)$(MANDIR)/ewm.1

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/ewm
	rm -f $(DESTDIR)$(BINDIR)/swpb
	rm -f $(DESTDIR)$(MANDIR)/ewm.1

clean:
	rm -f ewm *.o
	rm -rf config.h

.PHONY: all install uninstall clean
