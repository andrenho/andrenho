CC=g++
CFLAGS=-c -Wall -I. -g 
LDFLAGS=

SOURCES=main.cc world.cc city.cc
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=newhope

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cc.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)
