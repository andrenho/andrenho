OBJECTS = src/main.o \
	  src/gui/gui.o \
	  src/glue/glue.o

TCOD_CFLAGS = -I/c/andre/lib/libtcod-1.5.1/include 
TCOD_LIB = -L/c/andre/lib/libtcod-1.5.1/lib -ltcod-mingw

LUA_CFLAGS = -I/c/andre/desenv/lua/include
LUA_LIB = -L/c/andre/desenv/lua/lib -llua5.1

CFLAGS = $(TCOD_CFLAGS) $(LUA_CFLAGS) -g -Wall -Wextra  -Isrc -Isrc/gui -Isrc/glue
LIBS = $(TCOD_LIB) $(LUA_LIB) -g -Wall -Wextra

all: crescent

src/main.o: src/main.c
src/gui/gui.o: src/gui/gui.c src/gui/gui.h
src/glue/glue.o: src/glue/glue.c src/glue/glue.h

.c.o:
	gcc -c -o $@ $< $(CFLAGS)

clean:
	rm -rf $(OBJECTS) crescent crescent.exe

crescent: $(OBJECTS)
	gcc -o crescent $^ $(LIBS)

.PHONY: crescent
