#	MAKEFILE
CFLAGS = -g -Wall -Wshadow
GCC = gcc $(CFLAGS)
SRCS = runsim.c makeargv.c testsim.c
OBJS = $(SRCS:%.c=%.o)

proc_fan: $(OBJS)
	$(GCC) $(OBJS) -o proc_fan

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	rm -f *.o a.out proc_fan
