CC=gcc
CFLAGS=-g -c -fPIC
LD=gcc -shared

DYNLIB=dl
DYNSFX=so

all: libtemplates.a

libtemplates.a: templates.c templates.h extensions.c extensions.h
	$(CC) $(CFLAGS) templates.c
	$(CC) $(CFLAGS) extensions.c
	ar cr libtemplates.a templates.o extensions.o

SRCFILES=\
	README.txt \
	extensions.c \
	extensions.h \
	Makefile \
	templates.c \
	templates.h

tarball:
	tar cvf templates.tar $(SRCFILES)

clean:
	rm -f *.o
	rm -f *.${DYNSFX}
	rm -f *.a
	rm -f *.tar

