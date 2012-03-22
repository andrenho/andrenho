CC=g++
CFLAGS=-c -Wall -g -O0 `sdl-config --cflags` `freetype-config --cflags`
LDFLAGS=-g -O0 `sdl-config --libs` `freetype-config --libs`
SOURCES=main.cc options.cc terminal.cc screen.cc font.cc \
	filter_inexact.cc filter_scanline.cc
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=dumbterm

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cc.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(EXECUTABLE).exe
