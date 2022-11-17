CC=gcc
SRC=src
BUILD=build
LIBS=-lGL -lGLU -lglut -LGL -lX11 -lX11 -lm
LIBSDIR=-I/usr/X11R6/include -L/usr/lib -L/usr/X11R6/lib

all: TD2

TD3: trace clipping
	${CC} -o ${BUILD}/TD2 ${SRC}/TD2.c  ${BUILD}/trace.o ${BUILD}/clipping.o ${LIBS} ${LIBSDIR}
TD2: trace 
	${CC} -o ${BUILD}/TD2 ${SRC}/TD2.c  ${BUILD}/trace.o  ${LIBS} ${LIBSDIR} 

clipping: trace
	${CC} -c ${SRC}/clipping.c -o ${BUILD}/clipping.o ${BUILD}/trace.o ${LIBS} ${LIBSDIR}

trace:
	${CC} -c ${SRC}/trace.c -o ${BUILD}/trace.o ${LIBS} ${LIBSDIR}

clean:
	rm -f TD2 #*#