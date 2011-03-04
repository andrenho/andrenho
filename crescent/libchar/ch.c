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
		return TCOD_black;
	}
}


inline static int checkchar(lua_State *L, int stack)
{
	CHAR* c;
	const char* char_str = luaL_checkstring(L, stack);

	if(strlen(char_str) == 1)
		return char_str[0];
	else
	{
		HASH_FIND_STR(chars, char_str, c);
		if(c)
			return c->c;
		else
		{
			char buf[1024];
			sprintf(buf, "invalid char %s", char_str);
			luaL_argerror(L, stack, buf);
			return 0;
		}
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
	TCOD_key_t k;
	no_args();
	
again:
	k = TCOD_console_wait_for_keypress(true);

	if(k.pressed)
	{
		lua_newtable(L);
		lua_pushstring(L, "key"); lua_setfield(L, -2, "type");
		lua_pushfstring(L, "%c", k.c); lua_setfield(L, -2, "char");
		lua_pushfstring(L, "%s", key(k.vk)); lua_setfield(L, -2, "key");
		lua_pushboolean(L, k.lctrl | k.rctrl); lua_setfield(L, -2, "ctrl");
		return 1;
	}
}


// ch.set(char, x, y, [fg_color])
static int set(lua_State *L)
{
	int n = check_args(L, 3, 4);
	int c = checkchar(L, 1);
	int x = luaL_checkint(L, 2);
	int y = luaL_checkint(L, 3);
	if(n == 4)
	{
		TCOD_color_t fg = checkcolor(L, 4);
		TCOD_console_set_default_foreground(NULL, fg);
	}
	TCOD_console_put_char(NULL, x, y, c, 0);

	return 0;
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

