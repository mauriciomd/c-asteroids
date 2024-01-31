CC?=gcc
SDL2FLAGS=$(shell pkg-config sdl2 --cflags --libs)
SDL2FLAGS += -lSDL2_image
CFLAGS?=-std=c99 -Wall -pedantic -Werror -Wshadow -Wstrict-aliasing -Wstrict-overflow -lm

SRCDIR  = . 
SRCS    := $(shell find $(SRCDIR) -name '*.c')

build: 
	${CC} $< ${SRCS} ${CFLAGS} -O2 -o game $< ${SDL2FLAGS}

run: build
	./game

clean:
	rm -f game *.o
