#include <curses.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

int running = 1;
lua_State* L;

void error(lua_State *L, const char *fmt, ...) 
{
	va_list argp;
	va_start(argp, fmt);
	vfprintf(stderr, "%s", argp);
	va_end(argp);
	lua_close(L);
	exit(EXIT_FAILURE);
}

void load_script()
{
	L = lua_open();
	luaL_openlibs(L);
	if (luaL_dofile(L, "fcca.lua"))
		error(L, "cannot run configuration file: %s", 
				lua_tostring(L, -1));
}

void init_curses()
{
	initscr();
	raw();
	noecho();
	keypad(stdscr, TRUE);
}

void draw_screen()
{
	refresh();
}

void event()
{
	int ch = getch();
	switch(ch)
	{
		case 'q':
			running = 0;
			break;
	}
}

void close_curses()
{
	endwin();
}

void unload_lua()
{
	lua_close(L);
}

int main()
{
	load_script();
	init_curses();

	while(running)
	{
		draw_screen();
		event();
	}

	close_curses();
	unload_lua();

	return 0;
}
