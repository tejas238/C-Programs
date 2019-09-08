# NOTE: All indented lines are indented with a tab character.

CC=gcc
CFLAGS= -Wall -Og
DFLAGS= -g
PROGS=doMath

all: $(PROGS)

%: %.c
	$(CC) $(DFLAGS) $(CFLAGS) $< -o $@

clean:
	rm -f $(PROGS) *.o ~*
