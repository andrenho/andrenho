CC=g++
CFLAGS=-c -Wall -I. -g `sdl-config --cflags`
LDFLAGS=`sdl-config --libs`
SOURCES=main.cc city.cc ui.cc building.cc workplace.cc person.cc psyche.cc debug.cc
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=city

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cc.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)
