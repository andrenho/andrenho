#include <stdio.h>

#include <libtcod.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "colors.c"

#define no_args() check_args(L, 0, 0)

/* check number of arguments */
inline static int check_args(lua_State *L, int min, int max)
{
	int n = lua_gettop(L);
	if(n < min || n > max)
	{
		char buf[1024];
		sprintf(buf, "number of arguments should be between %d and %d",
				min, max);
		return luaL_argerror(L, n, buf);
	}
	else
		return n;
}


inline static TCOD_color_t checkcolor(lua_State *L, int stack)
{
	COLOR* c;
	const char* color_str = luaL_checkstring(L, stack);

	HASH_FIND_STR(colors, color_str, c);
	if(c)
		return c->color;
	else
	{
		char buf[1024];
		sprintf(buf, "invalid color %s", color_str);
		luaL_argerror(L, stack, buf);
		return TCOD_black; // ???
	}
}


static int init(lua_State *L)
{
	check_args(L, 3, 3);
	TCOD_console_init_root(
			luaL_checkint(L, 1), // w
			luaL_checkint(L, 2), // h
			luaL_checkstring(L, 3), // window name
			false, TCOD_RENDERER_GLSL);
	return 0;
}


static int clear(lua_State *L)
{
	no_args();
	TCOD_console_clear(NULL);
	return 0;
}


static int bg(lua_State *L)
{
	check_args(L, 1, 1);
	TCOD_color_t bg = checkcolor(L, 1);
	TCOD_console_set_default_background(NULL, bg);
	return 0;
}


static int flush(lua_State *L)
{
	no_args();
	TCOD_console_flush();
	return 0;
}


static int event(lua_State *L)
{
	no_args();
	TCOD_key_t key = TCOD_console_check_for_keypress(TCOD_KEY_PRESSED);

	if(key.vk == TCODK_NONE)
	{
		lua_pushnil(L);
	}
	else
	{

	}

	return 1;
}


static const struct luaL_reg ch [] = {
	{ "init", init },
	{ "clear", clear },
	{ "flush", flush },
	{ "bg", bg },
	{ "event", event },
	{ NULL, NULL }  /* sentinel */
};

int luaopen_ch (lua_State *L) 
{
	init_colors();
	luaL_openlib(L, "ch", ch, 0);
	return 1;
}

