# -*- Makefile -*-
SHELL=/bin/sh
CC=gcc

HEADERS_PATH=../../include/
SRC_PATH=../../src
HEADERS=$(wildcard ../../include/*.h)

CFLAGS=-Wall -g -O3 -ffast-math -fomit-frame-pointer -I$(HEADERS_PATH)
LDLIBS=-lm

DEPENDENCIES=$(SRC_PATH)/input_output.c

SRC=$(wildcard *.[ch])
EXE=unit-test-d-input.x

SAMPLE_INPUT=sample.inp

default: $(EXE)

$(EXE): $(SRC) $(HEADERS) $(DEPENDENCIES)
	$(CC) -o $@ $(CFLAGS) $^ $(LDLIBS)

clean:
	rm -f *.mod *.o *.x

check: $(EXE)
	./$(EXE) < $(SAMPLE_INPUT)

# compilation pattern rule for objects
%.o: %.c
	$(CC) -c $(CFLAGS) $<
