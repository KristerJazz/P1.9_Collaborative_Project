PROJECT_NAME=ljmd

ROOT_DIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

# Paths
LIB_PATH=$(ROOT_DIR)/lib
SRC_PATH=$(ROOT_DIR)/src
HEADER_PATH=$(ROOT_DIR)/include
EXE_PATH=$(ROOT_DIR)

# File names
EXE_FILE=$(PROJECT_NAME).x
EXE=$(EXE_PATH)/$(EXE_FILE)

SHARED_FILE=lib$(PROJECT_NAME).so
SHARED=$(LIB_PATH)/$(SHARED_FILE)
