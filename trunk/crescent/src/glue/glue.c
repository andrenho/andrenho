#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

int glue_init()
{
	lua_State *L = lua_open();
	luaL_openlibs(L);

	if (luaL_loadfile(L, "src/engine/game.lua") || lua_pcall(L, 0, 0, 0))
	{
        	fprintf(stderr, "cannot load engine: %s", lua_tostring(L, -1));
		return 0;
	}

	return 1;
}
