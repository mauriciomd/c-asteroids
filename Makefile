CC?=gcc
SDL2FLAGS=$(shell pkg-config sdl2 --cflags --libs)
CFLAGS?=-std=c99 -Wall -pedantic -Werror -Wshadow -Wstrict-aliasing -Wstrict-overflow

SRCDIR  = . 
SRCS    := $(shell find $(SRCDIR) -name '*.c')

build: 
	${CC} $< ${SRCS} ${CFLAGS} -O2 -o game $< ${SDL2FLAGS}

run: build
	time ./game

clean:
	rm -f game *.o
