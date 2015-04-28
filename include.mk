all: ${PROGS}

.cpp:
	g++ -m32 -o $@ $< -I/home/ytoyama/include/zmp -L/home/ytoyama/lib/zmp \
    -lRcControl -lBaseboard -lpthread

clean:
	rm -rf main *.o a.out

.PHONY: all clean