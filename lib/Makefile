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
EXE_PATH=..
EXE=ljmd.x

default: $(EXE_PATH)/$(EXE)

clean:
	rm -f *.mod *.o $(EXE_PATH)/$(EXE)

# linker rule
$(EXE_PATH)/$(EXE): $(OBJ) $(HEADERS)
	$(CC) -o $@ $(CFLAGS) $^ $(LDLIBS)

# compilation pattern rule for objects
%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) $<

