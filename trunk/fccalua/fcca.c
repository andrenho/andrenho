#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "fcca.h"

static void error (lua_State *L, const char *fmt, ...);


FCCA* fcca_init()
{
	FCCA* f = malloc(sizeof(FCCA));

	// initialize LUA
	f->L = lua_open();
	luaL_openlibs(f->L);

	// load script
	if (luaL_loadfile(f->L, "fcca.lua") || lua_pcall(f->L, 0, 0, 0))
		error(f->L, "cannot run configuration file: %s",
	       			lua_tostring(f->L, -1));

	return f;
}

int fcca_new_game(FCCA* f, int w, int h)
{
	// initialize game
	lua_getglobal(f->L, "new_game");
	lua_pushnumber(f->L, w);
	lua_pushnumber(f->L, h);
	if (lua_pcall(f->L, 2, 1, 0) != 0)
		error(f->L, "error running function `new_game': %s",
	       			lua_tostring(f->L, -1));
	lua_setglobal(f->L, "G");

	return -1;
}


void fcca_map_size(FCCA* f, int* w, int* h)
{
	
}


void fcca_close(FCCA* f)
{
	lua_close(f->L);
}


static void error (lua_State *L, const char *fmt, ...) 
{
	va_list argp;
	va_start(argp, fmt);
	vfprintf(stderr, "%s", argp);
	va_end(argp);
	lua_close(L);
	exit(EXIT_FAILURE);
}

