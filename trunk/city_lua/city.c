// gcc -o city -Wall city.c -IC:/andre/desenv/lua/include -LC:/andre/desenv/lua -llua5.1

#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <stdlib.h>

int main()
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	int status = luaL_loadfile(L, "main.lua");
	if(status)
	{
		fprintf(stderr, "Couldn't load file: %s\n", lua_tostring(L, -1));
		exit(1);
	}

	lua_close(L);
	return 0;
}
