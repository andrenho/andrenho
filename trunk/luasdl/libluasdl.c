#include <stdio.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "SDL.h"

static struct {
	char* name;
	long value;
} constants[] = {
	{ "INIT_TIMER", SDL_INIT_TIMER },
	{ "INIT_AUDIO", SDL_INIT_AUDIO },
	{ "INIT_VIDEO", SDL_INIT_VIDEO },
	{ "INIT_CDROM", SDL_INIT_CDROM },
	{ "INIT_JOYSTICK", SDL_INIT_JOYSTICK },
	{ "INIT_NOPARACHUTE", SDL_INIT_NOPARACHUTE },
	{ "INIT_EVENTTHREAD", SDL_INIT_EVENTTHREAD },
	{ "INIT_EVERYTHING", SDL_INIT_EVERYTHING },
	{ "SWSURFACE", SDL_SWSURFACE },
	{ "HWSURFACE", SDL_HWSURFACE },
	{ "ASYNCBLIT", SDL_ASYNCBLIT },
	{ "ANYFORMAT", SDL_ANYFORMAT },
	{ "HWPALETTE", SDL_HWPALETTE },
	{ "DOUBLEBUF", SDL_DOUBLEBUF },
	{ "FULLSCREEN", SDL_FULLSCREEN },
	{ "OPENGL", SDL_OPENGL },
	{ "OPENGLBLIT", SDL_OPENGLBLIT },
	{ "RESIZABLE", SDL_RESIZABLE },
	{ "NOFRAME", SDL_NOFRAME },
	{ "HWACCEL", SDL_HWACCEL },
	{ "RLEACCEL", SDL_RLEACCEL },
	{ "SRCALPHA", SDL_SRCALPHA },
	{ "SRCCOLORKEY", SDL_SRCCOLORKEY },
	{ "PREALLOC", SDL_PREALLOC },
	{ NULL, 0 },
};

static void init_constants(lua_State *L)
{
	lua_getglobal(L, "SDL");

	int i=0;
	while(constants[i].name)
	{
		lua_pushstring(L, constants[i].name);
		lua_pushnumber(L, constants[i].value);
		lua_settable(L, -3);
		i++;
	}
}


inline static int check_args(lua_State *L, int min, int max)
{
	int n = lua_gettop(L);
	if(n < min || n > max)
	{
		char buf[1024];
		sprintf(buf, "number of arguments should be between %d and %d",
				min, max);
		return luaL_argerror(L, n, buf);
	}
	else
		return n;
}


static void rect(lua_State *L, SDL_Rect r)
{
	lua_newtable(L);

	lua_pushinteger(L, r.x); lua_setfield(L, -2, "x");
	lua_pushinteger(L, r.y); lua_setfield(L, -2, "y");
	lua_pushinteger(L, r.w); lua_setfield(L, -2, "w");
	lua_pushinteger(L, r.h); lua_setfield(L, -2, "h");
}


SDL_Surface* get_surface(lua_State *L)
{
	lua_getfield (L, 1, "c_data");
	SDL_Surface* sf = lua_touserdata(L, -1);
	lua_pop(L, 1);
	return sf;
}


static void get_format(lua_State *L, SDL_PixelFormat* fmt)
{
	lua_newtable(L);

	// TODO - palette

	lua_pushinteger(L, fmt->BitsPerPixel);
	lua_setfield(L, -2, "BitsPerPixel");

	lua_pushinteger(L, fmt->BytesPerPixel);
	lua_setfield(L, -2, "BytesPerPixel");

	lua_pushinteger(L, fmt->Rloss);
	lua_setfield(L, -2, "Rloss");

	lua_pushinteger(L, fmt->Gloss);
	lua_setfield(L, -2, "Gloss");

	lua_pushinteger(L, fmt->Bloss);
	lua_setfield(L, -2, "Bloss");

	lua_pushinteger(L, fmt->Aloss);
	lua_setfield(L, -2, "Aloss");

	lua_pushinteger(L, fmt->Rshift);
	lua_setfield(L, -2, "Rshift");

	lua_pushinteger(L, fmt->Gshift);
	lua_setfield(L, -2, "Gshift");

	lua_pushinteger(L, fmt->Bshift);
	lua_setfield(L, -2, "Bshift");

	lua_pushinteger(L, fmt->Ashift);
	lua_setfield(L, -2, "Ashift");

	lua_pushinteger(L, fmt->Rmask);
	lua_setfield(L, -2, "Rmask");

	lua_pushinteger(L, fmt->Gmask);
	lua_setfield(L, -2, "Gmask");

	lua_pushinteger(L, fmt->Bmask);
	lua_setfield(L, -2, "Bmask");

	lua_pushinteger(L, fmt->Amask);
	lua_setfield(L, -2, "Amask");

	lua_pushinteger(L, fmt->colorkey);
	lua_setfield(L, -2, "colorkey");

	lua_pushinteger(L, fmt->alpha);
	lua_setfield(L, -2, "alpha");
}


static void update_sf(lua_State *L)
{
	lua_getfield(L, -1, "c_data");
	SDL_Surface* sf = lua_touserdata(L, -1);
	lua_pop(L, 1);

	lua_pushinteger(L, sf->flags);
	lua_setfield(L, -2, "flags");

	lua_pushinteger(L, sf->w);
	lua_setfield(L, -2, "w");

	lua_pushinteger(L, sf->h);
	lua_setfield(L, -2, "h");

	lua_pushinteger(L, sf->pitch);
	lua_setfield(L, -2, "pitch");

	get_format(L, sf->format);
	lua_setfield(L, -2, "format");

	// TODO - pixels

	rect(L, sf->clip_rect);
	lua_setfield(L, -2, "clip_rect");
}


static void create_sf(lua_State *L, SDL_Surface* sf)
{
	lua_newtable(L);
	luaL_getmetatable(L, "SDL.Surface");
	lua_setmetatable(L, -2);

	lua_pushstring(L, "c_data");
	lua_pushlightuserdata(L, sf);
	lua_settable(L, -3);

	update_sf(L);
}


static int Init(lua_State *L)
{
	Uint32 flags;
	if(check_args(L, 0, 1) == 0)
		flags = SDL_INIT_EVERYTHING;
	else
		flags = luaL_checklong(L, 1);

	lua_pushboolean(L, (SDL_Init(flags) != -1));
	return 1;
}


static int InitSubSystem(lua_State *L)
{
	check_args(L, 1, 1);
	lua_pushboolean(L, (SDL_InitSubSystem(luaL_checklong(L, 1)) != -1));
	return 1;
}


static int QuitSubSystem(lua_State *L)
{
	check_args(L, 1, 1);
	SDL_QuitSubSystem(luaL_checklong(L, 1));
	return 0;
}


static int Quit(lua_State *L)
{
	check_args(L, 0, 0);
	SDL_Quit();
	return 0;
}


static int WasInit(lua_State *L)
{
	Uint32 flags;
	if(check_args(L, 0, 1) == 0)
		flags = SDL_INIT_EVERYTHING;
	else
		flags = luaL_checklong(L, 1);

	lua_pushinteger(L, SDL_WasInit(flags));
	return 1;
}


static int GetError(lua_State *L)
{
	check_args(L, 0, 0);
	lua_pushstring(L, SDL_GetError());
	return 1;
}


static int Version(lua_State *L)
{
	check_args(L, 0, 0);
	SDL_version v;
	SDL_VERSION(&v);

	int i = 1;
	lua_newtable(L);
	lua_pushinteger(L, v.major);
	lua_rawseti(L, -2, i++);
	lua_pushinteger(L, v.minor);
	lua_rawseti(L, -2, i++);
	lua_pushinteger(L, v.patch);
	lua_rawseti(L, -2, i++);

	return 1;
}


static int GetVideoSurface(lua_State *L)
{
	check_args(L, 0, 0);
	SDL_Surface* sf = SDL_GetVideoSurface();
	create_sf(L, sf);
	return 1;
}


static int GetVideoInfo(lua_State *L)
{
	check_args(L, 0, 0);
	const SDL_VideoInfo* info = SDL_GetVideoInfo();

	lua_newtable(L);

	lua_pushboolean(L, info->hw_available);
	lua_setfield(L, -2, "hw_available");
	lua_pushboolean(L, info->wm_available);
	lua_setfield(L, -2, "wm_available");
	lua_pushboolean(L, info->blit_hw);
	lua_setfield(L, -2, "blit_hw");
	lua_pushboolean(L, info->blit_hw_CC);
	lua_setfield(L, -2, "blit_hw_CC");
	lua_pushboolean(L, info->blit_hw_A);
	lua_setfield(L, -2, "blit_hw_A");
	lua_pushboolean(L, info->blit_sw);
	lua_setfield(L, -2, "blit_sw");
	lua_pushboolean(L, info->blit_sw_CC);
	lua_setfield(L, -2, "blit_sw_CC");
	lua_pushboolean(L, info->blit_sw_A);
	lua_setfield(L, -2, "blit_sw_A");
	lua_pushinteger(L, info->video_mem);
	lua_setfield(L, -2, "video_mem");
	lua_pushinteger(L, info->current_w);
	lua_setfield(L, -2, "current_w");
	lua_pushinteger(L, info->current_h);
	lua_setfield(L, -2, "current_h");

	get_format(L, info->vfmt);
	lua_setfield(L, -2, "format");

	return 1;
}


static int SetVideoMode(lua_State *L)
{
	int nargs = check_args(L, 2, 4);

	int w = luaL_checkint(L, 1),
	    h = luaL_checkint(L, 2),
	    bpp = 0;
	Uint32 flags = SDL_SWSURFACE;

	if(nargs > 2)
		bpp = luaL_checkint(L, 3);
	if(nargs > 3)
		flags = luaL_checklong(L, 4);

	SDL_Surface* sf = SDL_SetVideoMode(w, h, bpp, flags);
	if(!sf)
		lua_pushnil(L);
	else
		create_sf(L, sf);
	return 1;
}


static int VideoDriverName(lua_State *L)
{
	check_args(L, 0, 0);

	char driver[256];
	if(SDL_VideoDriverName(driver, 256))
		lua_pushstring(L, driver);
	else
		lua_pushnil(L);
	return 1;
}


static int CreateRGBSurface(lua_State *L)
{
	int nargs = check_args(L, 4, 8);

	Uint32 flags = luaL_checklong(L, 1);
	int w = luaL_checklong(L, 2),
	    h = luaL_checklong(L, 3),
	    bpp = luaL_checklong(L, 4);

	int r=0, g=0, b=0, a=0;
	// TODO - other colors

	SDL_Surface* sf = SDL_CreateRGBSurface(flags, w, h, bpp, r, g, b, a);
	if(!sf)
		lua_pushnil(L);
	else
		create_sf(L, sf);
	return 1;
}


static int UpdateRect(lua_State *L)
{
	SDL_Surface* sf = get_surface(L);
	printf("%x\n", sf);
	return 0;
}


static const struct luaL_reg SDL[] = {
	{ "Init", Init },
	{ "InitSubSystem", InitSubSystem },
	{ "QuitSubSystem", QuitSubSystem },
	{ "Quit", Quit },
	{ "WasInit", WasInit },
	{ "GetError", GetError },
	{ "Version", Version },

	{ "GetVideoSurface", GetVideoSurface },
	{ "GetVideoInfo", GetVideoInfo },
	{ "SetVideoMode", SetVideoMode },
	{ "VideoDriverName", VideoDriverName },
	{ "CreateRGBSurface", CreateRGBSurface },

	{NULL, NULL}
};


static const struct luaL_reg SDL_Sf[] = {
	{ "UpdateRect", UpdateRect },
	{ NULL, NULL },
};


int luaopen_luasdl(lua_State *L)
{
	luaL_newmetatable(L, "SDL.Surface");
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_register(L, NULL, SDL_Sf);

	luaL_register(L, "SDL", SDL);
	init_constants(L);

	return 1;
}
