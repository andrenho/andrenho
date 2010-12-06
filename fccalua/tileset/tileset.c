#include <stdlib.h>
#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "SDL.h"
#include "SDL_image.h"

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
	unsigned char* layer[3];
	SDL_Surface* image[3][256];
} Tileset;


inline static Tileset* get_ts(lua_State* L)
{
	lua_getglobal(L, "self");
	lua_getfield(L, -1, "data");
	return lua_touserdata(L, -1);
}


// Tileset.set_char(layer, char, x, y)
static int Tileset_set_char(lua_State* L)
{
	// parameters
	int layer = luaL_checknumber(L, 1);
	int x = luaL_checknumber(L, 3);
	int y = luaL_checknumber(L, 4);
	unsigned char ch;
	if(lua_isnumber(L, 2))
		ch = (unsigned char)lua_tonumber(L, 2);
	else
		ch = (unsigned char)(luaL_checkstring(L, 2)[0]);

	Tileset* ts = get_ts(L);

	// checks
	if(layer < 0 || layer > 2)
		luaL_error(L, "Layer must be between 0 and 2");
	if(x < 0 || x >= ts->w)
		luaL_error(L, "X must be between 0 and %d", ts->w);
	if(y < 0 || y >= ts->h)
		luaL_error(L, "Y must be between 0 and %d", ts->h);

	// do
	ts->layer[layer][x + (y * ts->w)] = ch;

	return 0;
}

static int Tileset_load_image(lua_State* L)
{
	// parameters
	int layer = luaL_checknumber(L, 1);
	const char* image = luaL_checkstring(L, 3);
	int x = luaL_checknumber(L, 4);
	int y = luaL_checknumber(L, 5);
	unsigned char ch;
	if(lua_isnumber(L, 2))
		ch = (unsigned char)lua_tonumber(L, 2);
	else
		ch = (unsigned char)(luaL_checkstring(L, 2)[0]);

	Tileset* ts = get_ts(L);

	// checks
	if(layer < 0 || layer > 2)
		luaL_error(L, "Layer must be between 0 and 2");

	// load image
	SDL_Surface* sf = IMG_Load(image);
	if(!sf)
		luaL_error(L, "Invalid image file '%s'.", image);

	// create image
	image[layer][ch] = SDL_CreateRGBSurface(SDL_SWSURFACE, ts->tile_w,
			ts->tile_h, 32, 0, 0, 0, 0);
	// TODO ...
	
	SDL_FreeSurface(sf);
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
	SET_FUNCTION("self", "load_image", Tileset_load_image);

	// initialize scr
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	ts->w = 80; ts->h = 50;
	ts->scr = SDL_SetVideoMode(ts->w * ts->tile_w, ts->h * ts->tile_h,
			32, SDL_SWSURFACE);
	SDL_FillRect(ts->scr, NULL, SDL_MapRGB(ts->scr->format, 255, 255, 255));
	SDL_Flip(ts->scr);

	// initialize layers
	int i, j;
	for(i=0; i<3; i++)
	{
		ts->layer[i] = malloc(ts->w * ts->h);
		for(j=0; j<(ts->w * ts->h); j++)
			ts->layer[i][j] = ' ';
	}

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
