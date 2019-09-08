# NOTE: All indented lines are indented with a tab character.

CC=gcc
CFLAGS= -lm
DFLAGS= 
PROGS=fp_parse

all: $(PROGS)

%: %.c
	$(CC) $(DFLAGS) $< -o $@ $(CFLAGS)

clean:
	rm -f $(PROGS) *.o ~*
