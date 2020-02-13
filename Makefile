# -*- Makefile -*-
SHELL=/bin/sh

default: all

all:
	$(MAKE) $(MFLAGS) -C lib

clean:
	$(MAKE) $(MFLAGS) -C lib clean
	$(MAKE) $(MFLAGS) -C examples clean

check: all
	$(MAKE) $(MFLAGS) -C examples check
