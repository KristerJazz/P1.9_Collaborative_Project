# -*- Makefile -*-
SHELL=/bin/sh

# FIXME: Test D has been disable since it is not fully automated
SUBDIR = unit-test-a-force unit-test-b-velverlet unit-test-c-ekin \
				 unit-test-d-input

.SECONDEXPANSION:
CLEAN_SUBDIRS = $$(foreach subdir,$$(SUBDIR),$$(subdir)-clean)
BUILD_SUBDIRS = $$(foreach subdir,$$(SUBDIR),$$(subdir)-build)
CHECK_SUBDIRS = $$(foreach subdir,$$(SUBDIR),$$(subdir)-check)

default: build

%-build:
	make -C $* default
	
build: $(BUILD_SUBDIRS)

clean: $(CLEAN_SUBDIRS)

%-clean:
	make -C $* clean

check: build $(CHECK_SUBDIRS)

%-check:
	make -C $* check