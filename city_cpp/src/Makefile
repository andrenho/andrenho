CC=g++
CFLAGS=-c -Wall -I. -g `sdl-config --cflags`
LDFLAGS=`sdl-config --libs`
SOURCES=main.cc city/City.cc city/Person.cc ui/UI.cc ui/Util.cc
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=city_cpp

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cc.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)
