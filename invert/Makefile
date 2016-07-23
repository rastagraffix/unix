.POSIX:

BINDIR = /usr/local/bin
MANDIR = /usr/local/share/man
MAN1 = $(MANDIR)/man1

all:

install:
	install -c -m 555 invert.sh $(DESTDIR)$(BINDIR)/invert
	install -c -m 444 invert.1 $(DESTDIR)$(MAN1)/invert.1

clean:

.PHONY: clean install
