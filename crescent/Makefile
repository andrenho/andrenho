#LUA = -I/c/andre/desenv/lua/include -L/c/andre/desenv/lua/lib -llua5.1
#LIBTCOD = -I/c/andre/lib/libtcod-1.5.1/include -L/c/andre/lib/libtcod-1.5.1/lib -ltcod-mingw
#EXT=.dll
LIBTCOD =-fPIC -I/home/andre/data/src/libtcod-1.5.1/include -L/home/andre/data/src/libtcod-1.5.1/include -ltcod
EXT=.so

all:
	gcc -Wall -Wextra -shared -o ch$(EXT) libchar/ch.c $(LUA) $(LIBTCOD)

clean:
	rm ch$(EXT)
