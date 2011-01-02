LUA_CFLAGS=-I/c/andre/desenv/lua/include
LUA_LIBS=-L/c/andre/desenv/lua/lib -llua
EXTENSION=so

libluasdl.$(EXTENSION):
	gcc -fPIC -Wall -shared libluasdl.c -o luasdl.$(EXTENSION) $(LUA_CFLAGS) $(LUA_LIBS) `sdl-config --cflags --libs` -lSDL_image

test: libluasdl.$(EXTENSION)
	lua.exe test.lua
