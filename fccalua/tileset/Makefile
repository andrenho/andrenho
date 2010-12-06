CFLAGS = -Wall -g
LUA_INCLUDES = /usr/include/lua5.1

all:
	gcc -fPIC -shared -o tileset.so $(CFLAGS) -I$(LUA_INCLUDES) tileset.c `sdl-config --cflags --libs`

clean:
	rm tileset.so
