# -*- Makefile -*-
SHELL=/bin/sh
CC=gcc

HEADERS_PATH=../../include/
HEADERS=$(wildcard ../../include/*.h)

CFLAGS=-Wall -g -O3 -ffast-math -fomit-frame-pointer -I$(HEADERS_PATH)
LDLIBS=-lm

SRC=$(wildcard *.c)
EXE=unit-test-c-ekin.x

default: $(EXE)

$(EXE): $(SRC) $(HEADERS)
	$(CC) -o $@ $(CFLAGS) $^ $(LDLIBS)

clean:
	rm -f *.mod *.o *.x

check: $(EXE)
	./$(EXE)

# compilation pattern rule for objects
%.o: %.c
	$(CC) -c $(CFLAGS) $<
	
