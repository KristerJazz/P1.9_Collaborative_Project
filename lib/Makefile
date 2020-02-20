# -*- Makefile -*-
include ../Rules.mk

SHELL=/bin/sh
CC=gcc
CFLAGS:=-Wall -O3 -ffast-math -march=native -fomit-frame-pointer -I$(HEADER_PATH)
LDLIBS=-lmvec -lm

ifeq ("$(origin WITH_OMP)", "command line")
CFLAGS+=-fopenmp
endif

ifeq ("$(origin WITH_MORSE)", "command line")
CFLAGS+=-DWITH_MORSE
endif

# list of source files
SRC=$(wildcard $(SRC_PATH)/*.c)
HEADERS=$(wildcard $(HEADER_PATH)/*.h)
OBJ=$(SRC:$(SRC_PATH)/%.c=%.o)

ifeq ("$(origin WITH_OMP)", "command line")
CFLAGS+=-fopenmp
endif
ifeq ("$(origin WITH_MPI)", "command line")
CC=mpicc
CFLAGS+=-D_MPI
else
CC=gcc
endif

default: $(EXE) $(SHARED) $(HEADERS)

clean:
	rm -f *.mod *.o *.so ../*.x

# linker rule
$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)

$(SHARED): $(filter-out ljmd.o, $(OBJ))
	$(CC) -shared -o $@ $(CFLAGS) $^ $(LDLIBS)

# compilation pattern rule for objects
%.o: $(SRC_PATH)/%.c
	$(CC) -c $(CFLAGS) $< -fPIC
