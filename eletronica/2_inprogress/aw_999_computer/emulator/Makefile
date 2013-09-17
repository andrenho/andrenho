CC=gcc
CFLAGS=-Wall -g --std=c99

all: display emulator

emulator: emulator.o
	$(CC) -o $@ $< $(CFLAGS) $(LIBS)

display: display.o
	$(CC) -o $@ $< $(CFLAGS) $(LIBS) `sdl2-config --cflags --libs` `pkg-config --cflags --libs SDL2_image`

clean:
	rm -rf display *.o
