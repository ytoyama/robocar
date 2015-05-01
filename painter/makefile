CC = clang

RM = rm -rf
SYSTEM != uname

PROGS = painter

.if ${SYSTEM} == FreeBSD
INCDIR = -I/usr/local/include
LIBDIR = -L/usr/local/lib
.elif ${SYSTEM} == Linux
INCDIR = -I/usr/include
LIBDIR = -L/usr/lib
.endif
LIBS = -lX11
SRCS =

all: ${PROGS}

.c:
	${CC} -o ${.TARGET} ${.ALLSRC} ${SRCS} ${INCDIR} ${LIBDIR} ${LIBS}

clean:
	${RM} ${PROGS} *.o a.out *.core *.a

debug:
	@echo SYSTEM = ${SYSTEM}
	@echo INCDIR = ${INCDIR}
	@echo LIBDIR = ${LIBDIR}

.PHONY: all clean debug
