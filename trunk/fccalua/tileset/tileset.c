#include <stdlib.h>
#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "SDL.h"

#define SET_FUNCTION(table, name, function) { 	\
	lua_getglobal(L, table);		\
	lua_pushstring(L, name);		\
	lua_pushcfunction(L, function);		\
	lua_settable(L, -3);			\
}


typedef struct {
	int tile_w; 
	int tile_h;
	int w, h;
	SDL_Surface* scr;
} Tileset;

static int Tileset_set_char(lua_State* L)
{
	return 0;
}

static int Tileset_new(lua_State* L)
{
	int w = luaL_checknumber(L, 1);
	int h = luaL_checknumber(L, 2);

	// self = {}
	lua_newtable(L);
	lua_setglobal(L, "self");

	// self.data
	lua_getglobal(L, "self");
	lua_pushstring(L, "data");
	Tileset* ts = (Tileset*)lua_newuserdata(L, sizeof(Tileset));
	lua_settable(L, -3);
	ts->tile_w = w;
	ts->tile_h = h;

	// functions
	SET_FUNCTION("self", "set_char", Tileset_set_char);

	// initialize scr
	SDL_Init(SDL_INIT_VIDEO);
	ts->w = 80; ts->h = 50;
	ts->scr = SDL_SetVideoMode(ts->w * ts->tile_w, ts->h * ts->tile_h,
			32, SDL_SWSURFACE);
	SDL_FillRect(ts->scr, NULL, SDL_MapRGB(ts->scr->format, 255, 255, 255));

	// return self
	lua_getglobal(L, "self");
	return 1;
}

int luaopen_tileset(lua_State *L)
{
	// Tileset = {}
	lua_newtable(L);
	lua_setglobal(L, "Tileset");

	// function Tileset.new()
	SET_FUNCTION("Tileset", "new", Tileset_new);

	return 1;
}
