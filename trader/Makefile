CC=gcc
CFLAGS=-c -Wall -I. -g 
LDFLAGS=

SOURCES=main.c ui.c world.c port.c travel.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=seatrader

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)
