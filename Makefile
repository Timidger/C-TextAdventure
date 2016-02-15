# First target is default target, if you just type:  make

CC=gcc
CFLAGS=-g -O0 -I.
DEPS = player.h items.h

FILE=game.c player.c

default: run

run: build
	./game

gdb: build
	gdb game

build: ${FILE}
	$(CC) $(CFLAGS) -o game ${FILE}

clean:
	rm -f game a.out *~
