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


// ch.init()
static int init(lua_State *L)
{
	check_args(L, 3, 3);
	TCOD_console_init_root(
			luaL_checkint(L, 1), // w
			luaL_checkint(L, 2), // h
			luaL_checkstring(L, 3), // window name
			false, TCOD_RENDERER_SDL);
	return 0;
}


// ch.clear()
static int clear(lua_State *L)
{
	no_args();
	TCOD_console_clear(NULL);
	return 0;
}


// ch.bg(color)
static int bg(lua_State *L)
{
	check_args(L, 1, 1);
	TCOD_color_t bg = checkcolor(L, 1);
	TCOD_console_set_default_background(NULL, bg);
	return 0;
}


// ch.flush()
static int flush(lua_State *L)
{
	no_args();
	TCOD_console_flush();
	return 0;
}


// ch.wait_event()
static int wait_event(lua_State *L)
{
	TCOD_key_t key;
	no_args();
	
again:
	key = TCOD_console_check_for_keypress(TCOD_KEY_PRESSED);

	if(key.vk == TCODK_NONE)
	{
		TCOD_sys_sleep_milli(1000/30);
		goto again;
	}
	else
	{
		lua_newtable(L);
		lua_pushstring(L, "key"); lua_setfield(L, -2, "type");
		lua_pushfstring(L, "%c", key.c); lua_setfield(L, -2, "char");
		return 1;
	}
}


// ch.set(x, y, char, [fg_color])
static int set(lua_State *L)
{
	int n = check_args(L, 3, 4);
	int x = luaL_checkint(L, -1);
	int y = luaL_checkint(L, -2);
}


static const struct luaL_reg ch [] = {
	{ "init", init },
	{ "clear", clear },
	{ "flush", flush },
	{ "bg", bg },
	{ "wait_event", wait_event },
	{ "set", set },
	{ NULL, NULL }  /* sentinel */
};

int luaopen_ch (lua_State *L) 
{
	init_colors();
	init_chars();
	luaL_openlib(L, "ch", ch, 0);
	return 1;
}

