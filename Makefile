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

SOURCES = lifobuffer.c fifobuffer.c llbuffer.c lifotest.c fifotest.c lltest.c
OBJECTS = lifobuffer.o fifobuffer.o llbuffer.o lifotest.o fifotest.o lltest.o
	
# General compiler flags for gcc.
CFLAGS = gcc -Wall -Werror -O0 -std=c99

%.i : %.c
	$(CFLAGS) -E -o $@ $<

%.asm : %.c
	$(CFLAGS) -S $< -Xlinker ld -o $@

%.o : %.c
	$(CFLAGS) -c $< -o $@

.PHONY: debuglifo
debuglifo : $(OBJECTS)
	$(CFLAGS) lifobuffer.o -g lifotest.c -o LIFO.g -lpthread

.PHONY: debugfifo
debugfifo : $(OBJECTS)
	$(CFLAGS) fifobuffer.o -g fifotest.c -o FIFO.g -lpthread

.PHONY: debugll
debugll : $(OBJECTS)
	$(CFLAGS) llbuffer.o -g lltest.c -o LL.g -lpthread

.PHONY: buildlifo
buildlifo : $(OBJECTS)
	$(CFLAGS) lifobuffer.o lifotest.o -o LIFO.out -lpthread

.PHONY: buildfifo
buildfifo : $(OBJECTS)
	$(CFLAGS) fifobuffer.o fifotest.o -o FIFO.out -lpthread

.PHONY: buildll
buildll : $(OBJECTS)
	$(CFLAGS) llbuffer.o lltest.o -o LL.out -lpthread

.PHONY: clean
clean :
	rm -f *.o *.i *.asm *.map *.out *.g
