# First target is default target, if you just type:  make

BUILD_DIR=target
SOURCE_DIR=src
CC=gcc
CFLAGS=-g -O0 -I. -lm -Wall
DEPS=$(SOURCE_DIR)/player.h \
	 $(SOURCE_DIR)/items.h

OBJECTS=$(SOURCE_DIR)/player.o \
		$(SOURCE_DIR)/items.o \
		$(SOURCE_DIR)/display.o

MAIN_FILE=$(SOURCE_DIR)/game.c

default: run

run: build
	$(BUILD_DIR)/game

gdb: build
	gdb $(BUILD_DIR)/game

build: ${OBJECTS} ${DEPS} 
	$(CC) $(CFLAGS) -o target/game ${OBJECTS} ${MAIN_FILE}
	rm src/*.o

clean:
	rm -f target/game *~ src/*.o
