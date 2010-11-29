#ifndef FCCA_H
#define FCCA_H

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

typedef struct {
	lua_State *L;
} FCCA;

FCCA* fcca_init();
int new_game(FCCA* f, int w, int h);
void fcca_close(FCCA* f);

#endif
