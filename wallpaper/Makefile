UNAME := $(shell uname)

ifeq ($(UNAME), windows32)
	LUA_CFLAGS=-Ic:/andre/desenv/lua/include
	FREETYPE_CFLAGS=-IC:/andre/programas/gnuwin32/include/freetype2
	JPEG_CFLAGS=-IC:/andre/programas/gnuwin32/include
	LUA_LIBS=-Lc:/andre/desenv/lua/lib -llua5.1
	FREETYPE_LIBS=-Lc:/andre/programas/gnuwin32/lib -lfreetype
	JPEG_LIBS=-Lc:/andre/programas/gnuwin32/lib -ljpeg
	EXT=dll
else
	LUA_CFLAGS=`pkg-config --cflags lua5.1`
	FREETYPE_CFLAGS=`freetype-config --cflags`
	JPEG_CFLAGS=-I/usr/include
	LUA_LIBS=
	FREETYPE_LIBS=`freetype-config --libs`
	JPEG_LIBS=-ljpeg
	EXT=so
endif

CFLAGS=$(LUA_CFLAGS) $(FREETYPE_CFLAGS) $(JPEG_CFLAGS) -Wall -Wextra -O3
LIBS=$(LUA_LIBS) $(FREETYPE_LIBS) $(JPEG_LIBS)

all:
	gcc $(CFLAGS) -c -fPIC wp.c -o wp.o
	gcc -shared wp.o -o wp.$(EXT) $(LIBS)

clean:
	rm -rf wp.o wp.$(EXT)
