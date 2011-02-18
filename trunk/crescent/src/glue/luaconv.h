#ifndef LUACONV_H
#define LUACONV_H

#include <stdbool.h>

void lua(char* fmt, ...);
long lua_int(char* fmt, ...);
bool lua_bool(char* fmt, ...);

#endif
