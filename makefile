CC=gcc
SRC=src
BUILD=build
LIBS=-lGL -lGLU -lglut -LGL -lX11 -lX11 -lm
LIBSDIR=-I/usr/X11R6/include -L/usr/lib -L/usr/X11R6/lib

all: TD2 TD3 TD1

TD5:  translations
	${CC} ${SRC}/TD5.c -o ${BUILD}/TD5  ${BUILD}/pointManaging.o ${BUILD}/geometry.o ${LIBS} ${LIBSDIR} 
TD4: remplissage
	${CC} ${SRC}/TD4.c -o ${BUILD}/TD4 ${BUILD}/pointManaging.o ${BUILD}/trace.o ${BUILD}/filling.o ${LIBS} ${LIBSDIR} 
TD3: points trace clipping
	${CC} -o ${BUILD}/TD3 ${SRC}/TD3.c  ${BUILD}/pointManaging.o ${BUILD}/trace.o ${BUILD}/clipping.o ${LIBS} ${LIBSDIR}

TD2: points trace 
	${CC} -o ${BUILD}/TD2 ${SRC}/TD2.c  ${BUILD}/pointManaging.o ${BUILD}/trace.o  ${LIBS} ${LIBSDIR} 

TD1: points
	${CC} -o ${BUILD}/TD1 ${SRC}/TD1.c  ${BUILD}/pointManaging.o ${LIBS} ${LIBSDIR} 

remplissage: trace points
	${CC} -c ${SRC}/filling.c -o ${BUILD}/filling.o ${BUILD}/pointManaging.o ${BUILD}/trace.o
clipping: trace
	${CC} -c ${SRC}/clipping.c -o ${BUILD}/clipping.o ${BUILD}/trace.o ${LIBS} ${LIBSDIR}

trace:
	${CC} -c ${SRC}/trace.c -o ${BUILD}/trace.o ${LIBS} ${LIBSDIR}

translations: points	
	${CC} -c ${SRC}/geometry.c -o ${BUILD}/geometry.o ${BUILD}/pointManaging.o ${LIBS} ${LIBSDIR}

points: 
	${CC} -c ${SRC}/pointManaging.c -o ${BUILD}/pointManaging.o ${LIBS} ${LIBSDIR}


clean:
	rm -f TD2 #*#