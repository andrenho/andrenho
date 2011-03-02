#include <stdio.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

static int init(lua_State *L)
{
	printf("teste\n");
	return 1;
}

static const struct luaL_reg ch [] = {
	{ "init", init },
	{ NULL, NULL }  /* sentinel */
};

int luaopen_ch (lua_State *L) 
{
	luaL_openlib(L, "ch", ch, 0);
	return 1;
}

