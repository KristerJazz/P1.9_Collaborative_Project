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

PROJECT_NAME=ljmd

EXE_PATH=..
EXE=$(PROJECT_NAME).x

SHARED_PATH=.
SHARED_FILE=lib$(PROJECT_NAME).so

default: $(EXE_PATH)/$(EXE) $(SHARED_PATH)/$(SHARED_FILE)

clean:
	rm -f *.mod *.o *.so ../*.x

# linker rule
$(EXE_PATH)/$(EXE): $(SHARED_PATH)/$(SHARED_FILE)
	$(CC) -o $@ $(CFLAGS) $(LDLIBS) -l$(PROJECT_NAME) -L$(SHARED_PATH)

$(SHARED_PATH)/$(SHARED_FILE): $(OBJ) $(HEADERS)
	$(CC) -shared -o $@ $(CFLAGS) $^ $(LDLIBS)

# compilation pattern rule for objects
%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) $< -fPIC

