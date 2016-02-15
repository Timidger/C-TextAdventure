# First target is default target, if you just type:  make

CC=gcc
CFLAGS=-g -O0 -I.
DEPS=player.h items.h

OBJECTS=player.o \
		items.o \
		display.o

FILE=game.c player.c

default: run

run: build
	./game

gdb: build
	gdb game

build: ${OBJECTS} ${DEPS} 
	$(CC) $(CFLAGS) -o game ${OBJECTS} game.c

clean:
	rm -f game a.out *~ *.o
