#include <stdio.h>
#include <stdbool.h>

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

	if(lua_isnumber(L, stack))
	{
		return lua_tointeger(L, stack);
	}
	else
	{
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
	
	k = TCOD_console_wait_for_keypress(true);

	if(k.pressed)
	{
		lua_newtable(L);
		lua_pushstring(L, "key"); lua_setfield(L, -2, "type");
		lua_pushfstring(L, "%c", k.c); lua_setfield(L, -2, "char");
		lua_pushfstring(L, "%s", key(k.vk)); lua_setfield(L, -2, "key");
		lua_pushboolean(L, k.lctrl | k.rctrl); lua_setfield(L, -2, "ctrl");
	}
	else
		lua_pushnil(L);

	return 1;
}


// ch.check_event()
static int check_event(lua_State *L)
{
	TCOD_key_t k;
	no_args();
	
	k = TCOD_console_check_for_keypress(true);

	if(k.vk != TCODK_NONE && k.pressed)
	{
		lua_newtable(L);
		lua_pushstring(L, "key"); lua_setfield(L, -2, "type");
		lua_pushfstring(L, "%c", k.c); lua_setfield(L, -2, "char");
		lua_pushfstring(L, "%s", key(k.vk)); lua_setfield(L, -2, "key");
		lua_pushboolean(L, k.lctrl | k.rctrl); lua_setfield(L, -2, "ctrl");
	}
	else
		lua_pushnil(L);

	return 1;
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


// ch.print(text, x, y, [fg_color])
static int print(lua_State *L)
{
	int n = check_args(L, 3, 4);
	const char* c = luaL_checkstring(L, 1);
	int x = luaL_checkint(L, 2);
	int y = luaL_checkint(L, 3);
	if(n == 4)
	{
		TCOD_color_t fg = checkcolor(L, 4);
		TCOD_console_set_default_foreground(NULL, fg);
	}
	TCOD_console_print(NULL, x, y, c);

	lua_pushinteger(L, strlen(c));
	return 1;
}


// ch.frame(x, y, w, h, [fg_color, clear=false, overlap=true, double=false])
static int frame(lua_State *L)
{
	int n = check_args(L, 4, 8);
	int x = luaL_checkint(L, 1),
	    y = luaL_checkint(L, 2),
	    w = luaL_checkint(L, 3),
	    h = luaL_checkint(L, 4);
	bool overlap = true, clear=false, dbl = false;
	if(n > 4)
	{
		TCOD_color_t fg = checkcolor(L, 5);
		TCOD_console_set_default_foreground(NULL, fg);
	}
	if(n > 5)
		clear = lua_toboolean(L, 5);
	if(n > 6)
		overlap = lua_toboolean(L, 6);
	if(n > 7)
		dbl = lua_toboolean(L, 7);

	int xx, yy;

	// horizontal bars
	for(xx=(x+1); xx<=(x+w-1); xx++)
		for(yy=y; yy<=(y+h); yy+=h)
		{
			int ch = TCOD_console_get_char(NULL, xx, yy),
			    nch = TCOD_CHAR_HLINE;
			if(overlap)
			{
				if(ch == TCOD_CHAR_VLINE || ch == TCOD_CHAR_TEES || ch == TCOD_CHAR_TEEW)
					nch = TCOD_CHAR_CROSS;
				else if(ch == TCOD_CHAR_NW || ch == TCOD_CHAR_NE || ch == TCOD_CHAR_TEEN)
					nch = TCOD_CHAR_TEES;
				else if(ch == TCOD_CHAR_SE || ch == TCOD_CHAR_SW || ch == TCOD_CHAR_TEES)
					nch = TCOD_CHAR_TEEN;
			}
			TCOD_console_put_char(NULL, xx, yy, nch, 0);
		}

	// vertical bars
	for(yy=(y+1); yy<=(y+h-1); yy++)
		for(xx=x; xx<=(x+w); xx+=w)
		{
			int ch = TCOD_console_get_char(NULL, xx, yy),
			    nch = TCOD_CHAR_VLINE;
			if(overlap)
			{
				if(ch == TCOD_CHAR_HLINE || ch == TCOD_CHAR_TEEN || ch == TCOD_CHAR_TEES)
					nch = TCOD_CHAR_CROSS;
				else if(ch == TCOD_CHAR_NW || ch == TCOD_CHAR_SW || ch == TCOD_CHAR_TEEW)
					nch = TCOD_CHAR_TEEE;
				else if(ch == TCOD_CHAR_NE || ch == TCOD_CHAR_SE || ch == TCOD_CHAR_TEEE)
					nch = TCOD_CHAR_TEEW;
			}
			TCOD_console_put_char(NULL, xx, yy, nch, 0);
		}
	
	// corners
	int ch = TCOD_console_get_char(NULL, x, y);
	if(overlap && (ch == TCOD_CHAR_HLINE))
		TCOD_console_put_char(NULL, x, y, TCOD_CHAR_TEES, 0);
	else if(overlap && (ch == TCOD_CHAR_VLINE || ch == TCOD_CHAR_SW))
		TCOD_console_put_char(NULL, x, y, TCOD_CHAR_TEEE, 0);
	else if(overlap && (ch == TCOD_CHAR_SE))
		TCOD_console_put_char(NULL, x, y, TCOD_CHAR_CROSS, 0);
	else
		TCOD_console_put_char(NULL, x, y, TCOD_CHAR_NW, 0);

	ch = TCOD_console_get_char(NULL, (x+w), y);
	if(overlap && (ch == TCOD_CHAR_HLINE))
		TCOD_console_put_char(NULL, (x+w), y, TCOD_CHAR_TEES, 0);
	else if(overlap && (ch == TCOD_CHAR_VLINE || ch == TCOD_CHAR_SE))
		TCOD_console_put_char(NULL, (x+w), y, TCOD_CHAR_TEEW, 0);
	else if(overlap && (ch == TCOD_CHAR_SW))
		TCOD_console_put_char(NULL, (x+w), y, TCOD_CHAR_CROSS, 0);
	else
		TCOD_console_put_char(NULL, (x+w), y, TCOD_CHAR_NE, 0);

	ch = TCOD_console_get_char(NULL, x, (y+h));
	if(overlap && (ch == TCOD_CHAR_VLINE))
		TCOD_console_put_char(NULL, x, (y+h), TCOD_CHAR_TEEE, 0);
	else if(overlap && (ch == TCOD_CHAR_HLINE || ch == TCOD_CHAR_SE))
		TCOD_console_put_char(NULL, x, (y+h), TCOD_CHAR_TEEN, 0);
	else if(overlap && (ch == TCOD_CHAR_NE))
		TCOD_console_put_char(NULL, x, (y+h), TCOD_CHAR_CROSS, 0);
	else 
		TCOD_console_put_char(NULL, x, (y+h), TCOD_CHAR_SW, 0);
	
	ch = TCOD_console_get_char(NULL, (x+w), (y+h));
	if(overlap && (ch == TCOD_CHAR_VLINE))
		TCOD_console_put_char(NULL, (x+w), (y+h), TCOD_CHAR_TEEW, 0);
	else if(overlap && (ch == TCOD_CHAR_HLINE || ch == TCOD_CHAR_NE))
		TCOD_console_put_char(NULL, (x+w), (y+h), TCOD_CHAR_TEEN, 0);
	else if(overlap && (ch == TCOD_CHAR_NW))
		TCOD_console_put_char(NULL, (x+w), (y+h), TCOD_CHAR_CROSS, 0);
	else 
		TCOD_console_put_char(NULL, (x+w), (y+h), TCOD_CHAR_SE, 0);

	// clear
	if(clear)
		TCOD_console_rect(NULL, (x+1), (y+1), (w-1), (h-1), true, 0);

	return 1;
}


// ch.double_frame(x, y, w, h, [fg_color, clear=false])
static int double_frame(lua_State *L)
{
	int n = check_args(L, 4, 6);
	int x = luaL_checkint(L, 1),
	    y = luaL_checkint(L, 2),
	    w = luaL_checkint(L, 3),
	    h = luaL_checkint(L, 4);
	bool clear=false;
	if(n > 4)
	{
		TCOD_color_t fg = checkcolor(L, 5);
		TCOD_console_set_default_foreground(NULL, fg);
	}
	if(n > 5)
		clear = lua_toboolean(L, 5);

	int xx, yy;
	for(xx=(x+1); xx<(x+w); xx++)
	{
		TCOD_console_put_char(NULL, xx, y, TCOD_CHAR_DHLINE, 0);
		TCOD_console_put_char(NULL, xx, y+h, TCOD_CHAR_DHLINE, 0);
	}
	for(yy=(y+1); yy<(y+h); yy++)
	{
		TCOD_console_put_char(NULL, x, yy, TCOD_CHAR_DVLINE, 0);
		TCOD_console_put_char(NULL, x+w, yy, TCOD_CHAR_DVLINE, 0);
	}
	TCOD_console_put_char(NULL, x, y, TCOD_CHAR_DNW, 0);
	TCOD_console_put_char(NULL, x, (y+h), TCOD_CHAR_DSW, 0);
	TCOD_console_put_char(NULL, (x+w), y, TCOD_CHAR_DNE, 0);
	TCOD_console_put_char(NULL, (x+w), (y+h), TCOD_CHAR_DSE, 0);

	return 0;
}


// ch.elapsed_ms()
static int elapsed_ms(lua_State *L)
{
	no_args();
	lua_pushinteger(L, TCOD_sys_elapsed_milli());
	return 1;
}


// ch.sleep()
static int sleep(lua_State *L)
{
	check_args(L, 1, 1);
	TCOD_sys_sleep_milli(luaL_checklong(L, 1));
	return 0;
}


static const struct luaL_reg ch [] = {
	{ "init", init },
	{ "clear", clear },
	{ "flush", flush },
	{ "bg", bg },
	{ "wait_event", wait_event },
	{ "check_event", check_event },
	{ "set", set },
	{ "print", print },
	{ "frame", frame },
	{ "double_frame", double_frame },
	{ "elapsed_ms", elapsed_ms },
	{ "sleep", sleep },
	{ NULL, NULL }  /* sentinel */
};

int luaopen_ch (lua_State *L) 
{
	init_colors();
	init_chars();
	luaL_openlib(L, "ch", ch, 0);
	return 1;
}

