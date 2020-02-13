# -*- Makefile -*-
SHELL=/bin/sh
CC=gcc
HEADER_PATH=../include
CFLAGS=-Wall -g -O3 -ffast-math -fomit-frame-pointer -I$(HEADER_PATH)
LDLIBS=-lm

# list of source files
SRC=$(wildcard ../src/*.c)
HEADERS=$(wildcard ../include/*.h)
VPATH=../src
OBJ=$(SRC:../src/%.c=%.o)

default: ../ljmd-serial.x

clean:
	rm -f *.mod *.o ../ljmd-serial.x

# linker rule
../ljmd-serial.x: $(OBJ) $(HEADERS)
	$(CC) -o $@ $(CFLAGS) $^ $(LDLIBS)

# compilation pattern rule for objects
%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) $<

