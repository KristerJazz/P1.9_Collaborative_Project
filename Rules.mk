PROJECT_NAME=ljmd

ROOT_DIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

# Paths
LIB_PATH=$(ROOT_DIR)/lib
EXE_PATH=$(ROOT_DIR)

# File names
EXE_FILE=$(PROJECT_NAME).x
