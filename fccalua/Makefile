LUA_INCLUDES = -I/usr/include/lua5.1
#LUA_INCLUDES=-I/c/andre/desenv/lua/include
LUA_LIB=-L/c/andre/desenv/lua -llua5.1
SDL_INCLUDE_LIBS=`sdl-config --cflags --libs` -lSDL_image
CFLAGS=-Wall -g $(LUA_INCLUDES) $(LUA_LIB) $(SDL_INCLUDE_LIBS) -fPIC -shared 
EXT=.so

all:
	gcc -o libtileset$(EXT) tileset.c $(CFLAGS)

clean:
	rm tileset$(EXT)
