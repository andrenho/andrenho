CC=gcc
CFLAGS=-Wall -g -O0 --std=c99 `sdl2-config --cflags` `pkg-config --cflags SDL2_image`
LDFLAGS=`sdl2-config --libs` `pkg-config --libs SDL2_image`

emulator: display.o emulator.o ram.o

clean:
	rm -rf emulator *.o
