CC=gcc
LIBS=-lGL -lGLU -lglut -LGL -lX11 -lX11 -lm
LIBSDIR=-I/usr/X11R6/include -L/usr/lib -L/usr/X11R6/lib

all : TD2

TD2 : TD2.c
	${CC} TD2.c -o TD2 ${LIBS} ${LIBSDIR}

clean :
	rm -f TD2 #*#