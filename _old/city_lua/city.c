// gcc -o city -Wall city.c -IC:/andre/desenv/lua/include -LC:/andre/desenv/lua -llua5.1

#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <stdlib.h>
#include <string.h>

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

	int error;
	printf("%d\n", lua_gettop(L));
	error = luaL_loadbuffer(L, buff, strlen(buff), "my test") || 
		lua_pcall(L, 0, LUA_MULTRET, 0);
	if (error) 
	{
		fprintf(stderr, "%s", lua_tostring(L, -1));
		lua_pop(L, 1);  /* pop error message from the stack */
	}
	printf( "%d\n", lua_gettop(L) );
	printf( "%s\n", lua_tostring(L,-2) );
	printf( "%s\n", lua_tostring(L,-1) );

	lua_close(L);
	return 0;
}
