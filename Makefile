# First target is default target, if you just type:  make

FILE=game.c

default: run

run: build
	./game

gdb: build
	gdb game

build: ${FILE}
	gcc -g -O0 -o game ${FILE}

clean:
	rm -f game a.out *~
