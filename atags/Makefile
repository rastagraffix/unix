#	@(#)Makefile	8.1 (Berkeley) 6/6/93
# $FreeBSD: release/10.0.0/usr.bin/ctags/Makefile 201784 2010-01-08 11:16:58Z dwmalone $

BINDIR=/usr/local/bin/
MANDIR=/usr/local/man/man

PROG=		atags
MAN1=		atags.1
SRCS=		C.c atags.c fortran.c lisp.c print.c tree.c yacc.c
INCS=		atags.h
DEBUG_FLAGS=	-g
CFLAGS=		$(CPPFLAGS) $(DEBUG_FLAGS) -I.
CLEANFILES=	ATAGS

$(PROG): $(SRCS) $(INCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS)

clean:
	rm -rf *.o $(PROG) $(PROG).dSYM $(CLEANFILES)

install:
	install -d -m 755 -o root -g wheel $(DESTDIR)$(BINDIR)
	install -d -m 755 -o root -g wheel $(DESTDIR)$(MANDIR)1
	install -c -m 555 -o root -g wheel $(PROG) $(DESTDIR)$(BINDIR)
	install -c -m 444 -o root -g wheel $(MAN1) $(DESTDIR)$(MANDIR)1
