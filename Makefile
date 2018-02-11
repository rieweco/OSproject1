#	MAKEFILE
CFLAGS = -g -Wall -Wshadow -o
GCC = gcc $(CFLAGS)

all: runsim testsim

runsim: runsim.c makeargv.c
	$(GCC) $(CFLAGS) runsim runsim.c makeargv.c

testsim: testsim.c
	$(GCC) $(CFLAGS) testsim testsim.c

clean:
	rm -f *.o runsim testsim
