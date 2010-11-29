LUA_INCLUDE_DIR=/c/andre/desenv/lua/include
LUA_LIB_DIR=/c/andre/desenv/lua
CURSES_DIR=/c/andre/desenv/curses

LUA=-I$(LUA_INCLUDE_DIR) -L$(LUA_LIB_DIR) -llua5.1
CURSES=-I$(CURSES_DIR) -L$(CURSES_DIR) -lpdcurses

all:
	gcc -g -Wall -Wextra -o fcca fcca_curses.c fcca.c $(LUA) $(CURSES)

clean:
	rm fcca.exe
