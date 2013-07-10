#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "luaconv.h"

extern lua_State* L;

void lua(char* fmt, ...)
{
	char buf[512];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buf, 512, fmt, args);
	va_end(args);
	luaL_dostring(L, buf);
}


long lua_int(char* fmt, ...)
{
	char buf[512] = "return ";
	va_list args;
	va_start(args, fmt);
	vsnprintf(&buf[7], 512, fmt, args);
	va_end(args);
	luaL_dostring(L, buf);
	return lua_tointeger(L, -1);
}


bool lua_bool(char* fmt, ...)
{
	char buf[512] = "return ";
	va_list args;
	va_start(args, fmt);
	vsnprintf(&buf[7], 512, fmt, args);
	va_end(args);
	luaL_dostring(L, buf);
	return lua_toboolean(L, -1);
}


void lua_string(char* str, char* fmt, ...)
{
	char buf[512] = "return ";
	va_list args;
	va_start(args, fmt);
	vsnprintf(&buf[7], 512, fmt, args);
	va_end(args);
	luaL_dostring(L, buf);
	strncpy(str, lua_tostring(L, -1), 2047);
}
