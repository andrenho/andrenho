#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <stdarg.h>
#include <stdlib.h>
#include <math.h>

#include "glue.h"
#include "luaconv.h"

lua_State *L;
Game game;


// Load one tile from Lua
static void read_tile(int x, int y)
{
	int i = x + (y * game.w);
	game.map[i].terrain = lua_int("game.map[%d][%d].terrain.code", x, y);
	game.map[i].ovl = lua_int("game.map[%d][%d].terrain.ovl", x, y);
	game.map[i].river = lua_bool("game.map[%d][%d].river", x, y);
	game.map[i].special = lua_bool("game.map[%d][%d].special", x, y);
	game.map[i].road = lua_bool("game.map[%d][%d].road", x, y);
	game.map[i].plow = lua_bool("game.map[%d][%d].plow", x, y);
	game.map[i].rnd = rand() % 512;
}


// Initialize connection with Lua library and run scripts
int glue_init()
{
	L = lua_open();
	luaL_openlibs(L);

	if (luaL_loadfile(L, "src/engine/game.lua") || lua_pcall(L, 0, 0, 0))
	{
        	fprintf(stderr, "cannot load engine: %s", lua_tostring(L, -1));
		return 0;
	}

	return 1;
}


// Initialize a new game and load data do C
void glue_new_game(int w, int h)
{
	lua("game = Game:new(%d, %d, 'Phoenicia')", w, h);
	game.w = w;
	game.h = h;
	game.map = malloc(sizeof(Tile) * w * h);
	
	int x, y;
	for(x=1; x<w; x++)
		for(y=1; y<h; y++)
			read_tile(x, y);
}
