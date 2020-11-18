#
#***********************************************************************
#	Makefile for easy build process with appropriate flags.
#
#	USE:
#	  make [TARGET]
#
#	TARGET:
#	  <file>.o    - builds object file.
#	  <file>.i    - builds pre-processed file.
#	  <file>.asm  - builds assembly file.
#	  debug	      - builds a debuggable executable.
#	  build       - builds the executable.
#	  clean       - removes all generated files.
#
#
# Johannes Westman
# 2020-11-18
#**********************************************************************

SOURCES = lifobuffer.c lifotest.c
OBJECTS = lifobuffer.o lifotest.o
	
# General compiler flags for gcc.
CFLAGS = gcc -Wall -Werror -O0 -std=c99

%.i : %.c
	$(CFLAGS) -E -o $@ $<

%.asm : %.c
	$(CFLAGS) -S $< -Xlinker ld -o $@

%.o : %.c
	$(CFLAGS) -c $< -o $@

.PHONY: debug
debug : $(OBJECTS)
	$(CFLAGS) lifobuffer.o -g lifotest.c -o LIFO.g -lpthread

.PHONY: build
build : $(OBJECTS)
	$(CFLAGS) lifobuffer.o lifotest.o -o LIFO.out -lpthread

.PHONY: clean
clean :
	rm -f *.o *.i *.asm *.map *.out *.g
