CC=gcc
CFLAGS=-g -c -Wall
LDFLAGS=
SOURCES=main.c     book.h    \
	options.h  options.c \
	in_book.h  in_book.c \
	out_book.h out_book.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=book.exe

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm $(OBJECTS) $(EXECUTABLE)
