LIBDIR += -L/home/ytoyama/lib/zmp -L/usr/lib/i386-linux-gnu
INCDIR += -I/home/ytoyama/include/zmp
LIBS += -lRcControl -lBaseboard -lpthread -lRcImage -lIpm -lxml2

all: ${PROGS}

.cpp:
	g++ -m32 -o $@ $< $(INCDIR) $(LIBDIR) $(LIBS)

clean:
	rm -rf ${PROGS} *.o a.out

.PHONY: all clean
