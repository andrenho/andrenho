#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int running = 1;
lua_State* L;
int rx, ry = 0;
int map_w = 40, map_h = 20;
int colors = 1;


/***********
 *         *
 *   Lua   *
 *         *
 ***********/
void error(lua_State *L, const char *fmt, ...) 
{	
	va_list argp;
	va_start(argp, fmt);
	vfprintf(stderr, fmt, argp);
	va_end(argp);
	lua_close(L);
	exit(EXIT_FAILURE);
}

void lua_do(const char *fmt, ...)
{
	char buf[1024];
	va_list argp;
	va_start(argp, fmt);
	vsnprintf(buf, 1024, fmt, argp);
	va_end(argp);

	if(luaL_dostring(L, buf))
		error(L, "error running command '%s': %s", 
				buf, lua_tostring(L, -1));
}

int lua_is_nil(const char *fmt, ...)
{
	char buf[1024] = "return ";
	va_list argp;
	va_start(argp, fmt);
	vsnprintf(&buf[7], 1024, fmt, argp);
	va_end(argp);

	if(luaL_dostring(L, buf))
		error(L, "error running command '%s': %s", 
				buf, lua_tostring(L, -1));
	return lua_isnil(L, -1);
}

char lua_char(const char *fmt, ...)
{
	char buf[1024] = "return ";
	va_list argp;
	va_start(argp, fmt);
	vsnprintf(&buf[7], 1024, fmt, argp);
	va_end(argp);

	if(luaL_dostring(L, buf))
		error(L, "error running command '%s': %s", 
				buf, lua_tostring(L, -1));

	const char *s = lua_tostring(L, -1);
	if(s)
		return s[0];
	else
		return '\0';
}

char* lua_string(const char *fmt, ...)
{
	char buf[1024] = "return ";
	va_list argp;
	va_start(argp, fmt);
	vsnprintf(&buf[7], 1024, fmt, argp);
	va_end(argp);

	if(luaL_dostring(L, buf))
		error(L, "error running command '%s': %s", 
				buf, lua_tostring(L, -1));

	const char *s = lua_tostring(L, -1);
	return strdup(s);
}

int lua_int(const char *fmt, ...)
{
	char buf[1024] = "return ";
	va_list argp;
	va_start(argp, fmt);
	vsnprintf(&buf[7], 1024, fmt, argp);
	va_end(argp);

	if(luaL_dostring(L, buf))
		error(L, "error running command '%s': %s", 
				buf, lua_tostring(L, -1));

	return (int)lua_tointeger(L, -1);
}

void load_script()
{
	L = lua_open();
	luaL_openlibs(L);
	if(luaL_dofile(L, "cradle.lua"))
		error(L, "cannot run configuration file: %s", 
				lua_tostring(L, -1));
	lua_do("G = Game.new(%d, %d, { 'Assyria' })", map_w, map_h);
}

void unload_lua()
{
	lua_close(L);
}



/************
 *          *
 *  Curses  *
 *          *
 ************/
void init_curses()
{
	/*
tcod.console.initRoot(80, 50, 'CoC')
root=libtcod.TCODConsole_root
if not options.colors then
  root:setDefaultBackground(tcod.color.white)
  root:setDefaultForeground(tcod.color.darkGrey)
end
	*/
}

void draw_tile(int x, int y)
{
	if(lua_int("# G.map(%d,%d).units()",x, y) == 0)
	{
		switch(lua_char("G.map(%d,%d).terrain.char", x+rx, y+ry))
		{
			case 'O':
				/*
          root:putCharEx(x+rx, y+ry, string.byte(chr[1]),
                      chr[2], chr[3])
*/
				break;
			case 'G':
				// ...
				break;
			default:
				abort();
		}
	}
	else
	{
		switch(lua_char("G.map(%d,%d).units()[1].military.char", x, y))
		{
			case 'S':
				// ...
				break;
			default:
				abort();
		}
	}
}

void draw_status_line()
{
	/*
	// nation
	char* name = lua_string("G.player.name");
	char* unit = strdup("");
	int moves = 0;

	if(!lua_is_nil("G.selected"))
	{
		unit = lua_string("G.selected.name()");
		moves = lua_int("G.selected.moves");
	}
	mvprintw(LINES-2, 1, "%s   %s  M:%d", name, unit, moves);

	free(unit);

	// general info
	int year = lua_int("G.year") * -1;
	mvprintw(LINES-1, 1, "Year: %d B.C.", year);
	*/
}

void draw_screen()
{	
	int LINES = 80;
	int COLS = 80;

	// draw map
	int x, y;
	for(y=0; y<LINES-2; y++)
		for(x=0; x<COLS; x++)
			if(x+rx >= 0 && x+rx < map_w-1 
			&& y+ry >= 0 && y+ry < map_h-1)
				draw_tile(x, y);

	// status line
	draw_status_line();
	
	// refresh(); tcod.console.flush()

	// set cursor in the focused unit
	if(!lua_is_nil("G.selected"))
	{
		x = lua_int("G.selected.x");
		y = lua_int("G.selected.y");
//		if(x+rx >= 0 && x+rx < map_w-1 && y+ry >= 0 && y+ry <= map_h-1)
//			move(y+ry, x+rx);
	}
}

void event()
{
	int ch;// = getch(); ... tcod.console.waitForKeypress(true)
	switch(ch)
	{
		case 'q':
			running = 0;
			break;
		case '1': case 'j':
			if(!lua_is_nil("G.selected"))
				lua_do("G.selected.move(-1, 1)");
			break;
		case '2': case 'k':
			if(!lua_is_nil("G.selected"))
				lua_do("G.selected.move(0, 1)");
			break;
		case '3': case 'l':
			if(!lua_is_nil("G.selected"))
				lua_do("G.selected.move(1, 1)");
			break;
		case '4': case 'u':
			if(!lua_is_nil("G.selected"))
				lua_do("G.selected.move(-1, 0)");
			break;
		case '6': case 'o':
			if(!lua_is_nil("G.selected"))
				lua_do("G.selected.move(1, 0)");
			break;
		case '7':
			if(!lua_is_nil("G.selected"))
				lua_do("G.selected.move(-1, -1)");
			break;
		case '8':
			if(!lua_is_nil("G.selected"))
				lua_do("G.selected.move(0, -1)");
			break;
		case '9':
			if(!lua_is_nil("G.selected"))
				lua_do("G.selected.move(1, -1)");
			break;
		case ' ':
			lua_do("G.player.end_turn()");
			break;
		case 'w':
			lua_do("G.player.next_unit()");
			break;
	}
}

int main(int argc, char* argv[])
{
	int i;
	for(i=1; i<argc; i++)
		if(!strcmp(argv[i], "-bw"))
			colors = 0;

	load_script();
	init_curses();

	while(running)
	{
		draw_screen();
		event();
	}

	unload_lua();

	return 0;
}
