PROJECT_NAME=ljmd

ROOT_DIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

# Paths
LIB_PATH=$(ROOT_DIR)/lib
SRC_PATH=$(ROOT_DIR)/src
HEADER_PATH=$(ROOT_DIR)/include
EXE_PATH=$(ROOT_DIR)
PERF_PATH=$(ROOT_DIR)/perf
REFERENCE_PATH=$(ROOT_DIR)/reference
EXAMPLES_PATH=$(ROOT_DIR)/examples

# File names
EXE_FILE=$(PROJECT_NAME).x
EXE=$(EXE_PATH)/$(EXE_FILE)
PERF=$(PERF_PATH)/perf.data
PERF_RESULT=$(PERF_PATH)/stats.txt

SHARED_FILE=lib$(PROJECT_NAME).so
SHARED=$(LIB_PATH)/$(SHARED_FILE)

ifeq ("$(origin WITH_MPI)", "command line")
EXECUTER=time mpirun -np
NUM_PROC=$(WITH_MPI)
else
EXECUTER=time
endif
ifeq ("$(origin WITH_OMP)", "command line")
OMP_NUM_THREADS:=$(WITH_OMP)
endif

export LIB_PATH SHARED EXAMPLES_PATH ROOT_DIR OMP_NUM_THREADS
export ROOT_DIR
