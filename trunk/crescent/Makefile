LUA = -I/c/andre/desenv/lua/include -L/c/andre/desenv/lua/lib -llua5.1
LIBTCOD = -I/c/andre/lib/libtcod-1.5.1/include -L/c/andre/lib/libtcod-1.5.1/lib -ltcod-mingw

all:
	gcc -shared -o ch.dll libchar/ch.c $(LUA) $(LIBTCOD)

clean:
	rm ch.dll
