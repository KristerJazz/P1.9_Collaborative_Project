# -*- Makefile -*-
SHELL=/bin/sh

default: all

all:
	$(MAKE) $(MFLAGS) -C lib

clean:
	$(MAKE) $(MFLAGS) -C lib clean
	$(MAKE) $(MFLAGS) -C examples clean

check: serial
	$(MAKE) $(MFLAGS) -C examples check
