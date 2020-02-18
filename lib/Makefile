# -*- Makefile -*-
include ../Rules.mk

SHELL=/bin/sh
CC=gcc
CFLAGS:=-Wall -g -O3 -ffast-math -fomit-frame-pointer -I$(HEADER_PATH)
LDLIBS=-lm

ifeq ("$(origin WITH_OMP)", "command line")
CFLAGS+=-fopenmp
endif

# list of source files
SRC=$(wildcard $(SRC_PATH)/*.c)
HEADERS=$(wildcard $(HEADER_PATH)/*.h)
OBJ=$(SRC:$(SRC_PATH)/%.c=%.o)

default: $(EXE) $(SHARED)

clean:
	rm -f *.mod *.o *.so ../*.x

# linker rule
$(EXE): $(SHARED) $(HEADERS)
	$(CC) -o $@ $(CFLAGS) $(LDLIBS) -l$(PROJECT_NAME) -L$(LIB_PATH)

$(SHARED): $(OBJ)
	$(CC) -shared -o $@ $(CFLAGS) $^ $(LDLIBS)

# compilation pattern rule for objects
%.o: $(SRC_PATH)/%.c
	$(CC) -c $(CFLAGS) $< -fPIC
