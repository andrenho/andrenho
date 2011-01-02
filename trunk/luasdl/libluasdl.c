#include <stdio.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "SDL.h"
#include "SDL_image.h"

/* list of SDL constants */
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
	{ "LOGPAL", SDL_LOGPAL },
	{ "PHYSPAL", SDL_PHYSPAL },
	
	{ "GRAB_QUERY", SDL_GRAB_QUERY },
	{ "GRAB_OFF", SDL_GRAB_OFF },
	{ "GRAB_ON", SDL_GRAB_ON },

	{ "ACTIVEEVENT", SDL_ACTIVEEVENT },
	{ "KEYUP", SDL_KEYUP },
	{ "KEYDOWN", SDL_KEYDOWN },
	{ "MOUSEMOTION", SDL_MOUSEMOTION },
	{ "MOUSEBUTTONUP", SDL_MOUSEBUTTONUP },
	{ "MOUSEBUTTONDOWN", SDL_MOUSEBUTTONDOWN },
	{ "JOYAXISMOTION", SDL_JOYAXISMOTION },
	{ "JOYBALLMOTION", SDL_JOYBALLMOTION },
	{ "JOYHATMOTION", SDL_JOYHATMOTION },
	{ "JOYBUTTONUP", SDL_JOYBUTTONUP },
	{ "JOYBUTTONDOWN", SDL_JOYBUTTONDOWN },
	{ "VIDEORESIZE", SDL_VIDEORESIZE },
	{ "VIDEOEXPOSE", SDL_VIDEOEXPOSE },
	{ "QUIT", SDL_QUIT },
	{ "USEREVENT", SDL_USEREVENT },
	{ "SYSWMEVENT", SDL_SYSWMEVENT },

	{ "APPMOUSEFOCUS", SDL_APPMOUSEFOCUS },
	{ "APPINPUTFOCUS", SDL_APPINPUTFOCUS },
	{ "APPACTIVE", SDL_APPACTIVE },

	{ "PRESSED", SDL_PRESSED },
	{ "RELEASED", SDL_RELEASED },
	{ "KMOD_NONE", KMOD_NONE },
	{ "KMOD_LSHIFT", KMOD_LSHIFT },
	{ "KMOD_RSHIFT", KMOD_RSHIFT },
	{ "KMOD_LCTRL", KMOD_LCTRL },
	{ "KMOD_RCTRL", KMOD_RCTRL },
	{ "KMOD_LALT", KMOD_LALT },
	{ "KMOD_RALT", KMOD_RALT },
	{ "KMOD_LMETA", KMOD_LMETA },
	{ "KMOD_RMETA", KMOD_RMETA },
	{ "KMOD_NUM", KMOD_NUM },
	{ "KMOD_CAPS", KMOD_CAPS },
	{ "KMOD_MODE", KMOD_MODE },
	{ "KMOD_CTRL", KMOD_CTRL },
	{ "KMOD_SHIFT", KMOD_SHIFT },
	{ "KMOD_ALT", KMOD_ALT },
	{ "KMOD_META", KMOD_META },

	{ "BACKSPACE", SDLK_BACKSPACE },
	{ "TAB", SDLK_TAB },
	{ "CLEAR", SDLK_CLEAR },
	{ "RETURN", SDLK_RETURN },
	{ "PAUSE", SDLK_PAUSE },
	{ "ESCAPE", SDLK_ESCAPE },
	{ "SPACE", SDLK_SPACE },
	{ "EXCLAIM", SDLK_EXCLAIM },
	{ "QUOTEDBL", SDLK_QUOTEDBL },
	{ "HASH", SDLK_HASH },
	{ "DOLLAR", SDLK_DOLLAR },
	{ "AMPERSAND", SDLK_AMPERSAND },
	{ "QUOTE", SDLK_QUOTE },
	{ "LEFTPAREN", SDLK_LEFTPAREN },
	{ "RIGHTPAREN", SDLK_RIGHTPAREN },
	{ "ASTERISK", SDLK_ASTERISK },
	{ "PLUS", SDLK_PLUS },
	{ "COMMA", SDLK_COMMA },
	{ "MINUS", SDLK_MINUS },
	{ "PERIOD", SDLK_PERIOD },
	{ "SLASH", SDLK_SLASH },
	{ "N0", SDLK_0 },
	{ "N1", SDLK_1 },
	{ "N2", SDLK_2 },
	{ "N3", SDLK_3 },
	{ "N4", SDLK_4 },
	{ "N5", SDLK_5 },
	{ "N6", SDLK_6 },
	{ "N7", SDLK_7 },
	{ "N8", SDLK_8 },
	{ "N9", SDLK_9 },
	{ "COLON", SDLK_COLON },
	{ "SEMICOLON", SDLK_SEMICOLON },
	{ "LESS", SDLK_LESS },
	{ "EQUALS", SDLK_EQUALS },
	{ "GREATER", SDLK_GREATER },
	{ "QUESTION", SDLK_QUESTION },
	{ "AT", SDLK_AT },
	{ "LEFTBRACKET", SDLK_LEFTBRACKET },
	{ "BACKSLASH", SDLK_BACKSLASH },
	{ "RIGHTBRACKET", SDLK_RIGHTBRACKET },
	{ "CARET", SDLK_CARET },
	{ "UNDERSCORE", SDLK_UNDERSCORE },
	{ "BACKQUOTE", SDLK_BACKQUOTE },
	{ "a", SDLK_a },
	{ "b", SDLK_b },
	{ "c", SDLK_c },
	{ "d", SDLK_d },
	{ "e", SDLK_e },
	{ "f", SDLK_f },
	{ "g", SDLK_g },
	{ "h", SDLK_h },
	{ "i", SDLK_i },
	{ "j", SDLK_j },
	{ "k", SDLK_k },
	{ "l", SDLK_l },
	{ "m", SDLK_m },
	{ "n", SDLK_n },
	{ "o", SDLK_o },
	{ "p", SDLK_p },
	{ "q", SDLK_q },
	{ "r", SDLK_r },
	{ "s", SDLK_s },
	{ "t", SDLK_t },
	{ "u", SDLK_u },
	{ "v", SDLK_v },
	{ "w", SDLK_w },
	{ "x", SDLK_x },
	{ "y", SDLK_y },
	{ "z", SDLK_z },
	{ "DELETE", SDLK_DELETE },
	{ "WORLD_0", SDLK_WORLD_0 },
	{ "WORLD_1", SDLK_WORLD_1 },
	{ "WORLD_2", SDLK_WORLD_2 },
	{ "WORLD_3", SDLK_WORLD_3 },
	{ "WORLD_4", SDLK_WORLD_4 },
	{ "WORLD_5", SDLK_WORLD_5 },
	{ "WORLD_6", SDLK_WORLD_6 },
	{ "WORLD_7", SDLK_WORLD_7 },
	{ "WORLD_8", SDLK_WORLD_8 },
	{ "WORLD_9", SDLK_WORLD_9 },
	{ "WORLD_10", SDLK_WORLD_10 },
	{ "WORLD_11", SDLK_WORLD_11 },
	{ "WORLD_12", SDLK_WORLD_12 },
	{ "WORLD_13", SDLK_WORLD_13 },
	{ "WORLD_14", SDLK_WORLD_14 },
	{ "WORLD_15", SDLK_WORLD_15 },
	{ "WORLD_16", SDLK_WORLD_16 },
	{ "WORLD_17", SDLK_WORLD_17 },
	{ "WORLD_18", SDLK_WORLD_18 },
	{ "WORLD_19", SDLK_WORLD_19 },
	{ "WORLD_20", SDLK_WORLD_20 },
	{ "WORLD_21", SDLK_WORLD_21 },
	{ "WORLD_22", SDLK_WORLD_22 },
	{ "WORLD_23", SDLK_WORLD_23 },
	{ "WORLD_24", SDLK_WORLD_24 },
	{ "WORLD_25", SDLK_WORLD_25 },
	{ "WORLD_26", SDLK_WORLD_26 },
	{ "WORLD_27", SDLK_WORLD_27 },
	{ "WORLD_28", SDLK_WORLD_28 },
	{ "WORLD_29", SDLK_WORLD_29 },
	{ "WORLD_30", SDLK_WORLD_30 },
	{ "WORLD_31", SDLK_WORLD_31 },
	{ "WORLD_32", SDLK_WORLD_32 },
	{ "WORLD_33", SDLK_WORLD_33 },
	{ "WORLD_34", SDLK_WORLD_34 },
	{ "WORLD_35", SDLK_WORLD_35 },
	{ "WORLD_36", SDLK_WORLD_36 },
	{ "WORLD_37", SDLK_WORLD_37 },
	{ "WORLD_38", SDLK_WORLD_38 },
	{ "WORLD_39", SDLK_WORLD_39 },
	{ "WORLD_40", SDLK_WORLD_40 },
	{ "WORLD_41", SDLK_WORLD_41 },
	{ "WORLD_42", SDLK_WORLD_42 },
	{ "WORLD_43", SDLK_WORLD_43 },
	{ "WORLD_44", SDLK_WORLD_44 },
	{ "WORLD_45", SDLK_WORLD_45 },
	{ "WORLD_46", SDLK_WORLD_46 },
	{ "WORLD_47", SDLK_WORLD_47 },
	{ "WORLD_48", SDLK_WORLD_48 },
	{ "WORLD_49", SDLK_WORLD_49 },
	{ "WORLD_50", SDLK_WORLD_50 },
	{ "WORLD_51", SDLK_WORLD_51 },
	{ "WORLD_52", SDLK_WORLD_52 },
	{ "WORLD_53", SDLK_WORLD_53 },
	{ "WORLD_54", SDLK_WORLD_54 },
	{ "WORLD_55", SDLK_WORLD_55 },
	{ "WORLD_56", SDLK_WORLD_56 },
	{ "WORLD_57", SDLK_WORLD_57 },
	{ "WORLD_58", SDLK_WORLD_58 },
	{ "WORLD_59", SDLK_WORLD_59 },
	{ "WORLD_60", SDLK_WORLD_60 },
	{ "WORLD_61", SDLK_WORLD_61 },
	{ "WORLD_62", SDLK_WORLD_62 },
	{ "WORLD_63", SDLK_WORLD_63 },
	{ "WORLD_64", SDLK_WORLD_64 },
	{ "WORLD_65", SDLK_WORLD_65 },
	{ "WORLD_66", SDLK_WORLD_66 },
	{ "WORLD_67", SDLK_WORLD_67 },
	{ "WORLD_68", SDLK_WORLD_68 },
	{ "WORLD_69", SDLK_WORLD_69 },
	{ "WORLD_70", SDLK_WORLD_70 },
	{ "WORLD_71", SDLK_WORLD_71 },
	{ "WORLD_72", SDLK_WORLD_72 },
	{ "WORLD_73", SDLK_WORLD_73 },
	{ "WORLD_74", SDLK_WORLD_74 },
	{ "WORLD_75", SDLK_WORLD_75 },
	{ "WORLD_76", SDLK_WORLD_76 },
	{ "WORLD_77", SDLK_WORLD_77 },
	{ "WORLD_78", SDLK_WORLD_78 },
	{ "WORLD_79", SDLK_WORLD_79 },
	{ "WORLD_80", SDLK_WORLD_80 },
	{ "WORLD_81", SDLK_WORLD_81 },
	{ "WORLD_82", SDLK_WORLD_82 },
	{ "WORLD_83", SDLK_WORLD_83 },
	{ "WORLD_84", SDLK_WORLD_84 },
	{ "WORLD_85", SDLK_WORLD_85 },
	{ "WORLD_86", SDLK_WORLD_86 },
	{ "WORLD_87", SDLK_WORLD_87 },
	{ "WORLD_88", SDLK_WORLD_88 },
	{ "WORLD_89", SDLK_WORLD_89 },
	{ "WORLD_90", SDLK_WORLD_90 },
	{ "WORLD_91", SDLK_WORLD_91 },
	{ "WORLD_92", SDLK_WORLD_92 },
	{ "WORLD_93", SDLK_WORLD_93 },
	{ "WORLD_94", SDLK_WORLD_94 },
	{ "WORLD_95", SDLK_WORLD_95 },
	{ "KP0", SDLK_KP0 },
	{ "KP1", SDLK_KP1 },
	{ "KP2", SDLK_KP2 },
	{ "KP3", SDLK_KP3 },
	{ "KP4", SDLK_KP4 },
	{ "KP5", SDLK_KP5 },
	{ "KP6", SDLK_KP6 },
	{ "KP7", SDLK_KP7 },
	{ "KP8", SDLK_KP8 },
	{ "KP9", SDLK_KP9 },
	{ "KP_PERIOD", SDLK_KP_PERIOD },
	{ "KP_DIVIDE", SDLK_KP_DIVIDE },
	{ "KP_MULTIPLY", SDLK_KP_MULTIPLY },
	{ "KP_MINUS", SDLK_KP_MINUS },
	{ "KP_PLUS", SDLK_KP_PLUS },
	{ "KP_ENTER", SDLK_KP_ENTER },
	{ "KP_EQUALS", SDLK_KP_EQUALS },
	{ "UP", SDLK_UP },
	{ "DOWN", SDLK_DOWN },
	{ "RIGHT", SDLK_RIGHT },
	{ "LEFT", SDLK_LEFT },
	{ "INSERT", SDLK_INSERT },
	{ "HOME", SDLK_HOME },
	{ "END", SDLK_END },
	{ "PAGEUP", SDLK_PAGEUP },
	{ "PAGEDOWN", SDLK_PAGEDOWN },
	{ "F1", SDLK_F1 },
	{ "F2", SDLK_F2 },
	{ "F3", SDLK_F3 },
	{ "F4", SDLK_F4 },
	{ "F5", SDLK_F5 },
	{ "F6", SDLK_F6 },
	{ "F7", SDLK_F7 },
	{ "F8", SDLK_F8 },
	{ "F9", SDLK_F9 },
	{ "F10", SDLK_F10 },
	{ "F11", SDLK_F11 },
	{ "F12", SDLK_F12 },
	{ "F13", SDLK_F13 },
	{ "F14", SDLK_F14 },
	{ "F15", SDLK_F15 },
	{ "NUMLOCK", SDLK_NUMLOCK },
	{ "CAPSLOCK", SDLK_CAPSLOCK },
	{ "SCROLLOCK", SDLK_SCROLLOCK },
	{ "RSHIFT", SDLK_RSHIFT },
	{ "LSHIFT", SDLK_LSHIFT },
	{ "RCTRL", SDLK_RCTRL },
	{ "LCTRL", SDLK_LCTRL },
	{ "RALT", SDLK_RALT },
	{ "LALT", SDLK_LALT },
	{ "RMETA", SDLK_RMETA },
	{ "LMETA", SDLK_LMETA },
	{ "LSUPER", SDLK_LSUPER },
	{ "RSUPER", SDLK_RSUPER },
	{ "MODE", SDLK_MODE },
	{ "COMPOSE", SDLK_COMPOSE },
	{ "HELP", SDLK_HELP },
	{ "PRINT", SDLK_PRINT },
	{ "SYSREQ", SDLK_SYSREQ },
	{ "BREAK", SDLK_BREAK },
	{ "MENU", SDLK_MENU },
	{ "POWER", SDLK_POWER },
	{ "EURO", SDLK_EURO },
	{ "UNDO", SDLK_UNDO },

	{ "BUTTON_LEFT", SDL_BUTTON_LEFT },
	{ "BUTTON_MIDDLE", SDL_BUTTON_MIDDLE },
	{ "BUTTON_RIGHT", SDL_BUTTON_RIGHT },
	{ "BUTTON_WHEELUP", SDL_BUTTON_WHEELUP },
	{ "BUTTON_WHEELDOWN", SDL_BUTTON_WHEELDOWN },

	{ "IGNORE", SDL_IGNORE },
	{ "ENABLE", SDL_ENABLE },
	{ "QUERY", SDL_QUERY },

	{ NULL, 0 },
};


/* initialize SDL constants */
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


/*
 *
 * HELPER FUNCTIONS
 *
 */


/* check number of arguments */
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


/* create a lua SDL_Rect */
static void rect(lua_State *L, SDL_Rect r)
{
	lua_newtable(L);

	lua_pushinteger(L, r.x); lua_setfield(L, -2, "x");
	lua_pushinteger(L, r.y); lua_setfield(L, -2, "y");
	lua_pushinteger(L, r.w); lua_setfield(L, -2, "w");
	lua_pushinteger(L, r.h); lua_setfield(L, -2, "h");
}


/* convert a LUA surface to SDL */
SDL_Surface* convert_surface(lua_State *L, int idx)
{
	lua_getfield (L, idx, "c_data");
	SDL_Surface* sf = lua_touserdata(L, -1);
	lua_pop(L, 1);
	return sf;
}


/* convert a LUA PixelFormat to SDL */
SDL_PixelFormat* convert_format(lua_State *L, int idx)
{
	lua_getfield(L, idx, "c_data");
	SDL_PixelFormat* fmt = lua_touserdata(L, -1);
	lua_pop(L, 1);
	return fmt;
}


/* convert a SDL_Rect to LUA */
SDL_Rect convert_rect(lua_State *L, int idx)
{
	int x, y, w, h;

	lua_getfield(L, idx, "x");
	if(lua_isnil(L, -1))
	{
		lua_pop(L, 1);
		lua_rawgeti(L, idx, 1); x = lua_tointeger(L, -1); lua_pop(L, 1);
		lua_rawgeti(L, idx, 2); y = lua_tointeger(L, -1); lua_pop(L, 1);
		lua_rawgeti(L, idx, 3); w = lua_tointeger(L, -1); lua_pop(L, 1);
		lua_rawgeti(L, idx, 4); h = lua_tointeger(L, -1); lua_pop(L, 1);
	}
	else
	{
		x = lua_tointeger(L, -1); lua_pop(L, 1);
		lua_getfield(L, idx, "y"); y = lua_tointeger(L, -1); lua_pop(L, 1);
		lua_getfield(L, idx, "w"); w = lua_tointeger(L, -1); lua_pop(L, 1);
		lua_getfield(L, idx, "h"); h = lua_tointeger(L, -1); lua_pop(L, 1);
	}

	return (SDL_Rect) { x, y, w, h };
}


/* convert a LUA color to SDL_Color */
SDL_Color convert_color(lua_State *L, int idx)
{
	int r, g, b;

	lua_getfield(L, idx, "r");
	if(lua_isnil(L, -1))
	{
		lua_pop(L, 1);
		lua_rawgeti(L, idx, 1); r = lua_tointeger(L, -1); lua_pop(L, 1);
		lua_rawgeti(L, idx, 2); g = lua_tointeger(L, -1); lua_pop(L, 1);
		lua_rawgeti(L, idx, 3); b = lua_tointeger(L, -1); lua_pop(L, 1);
	}
	else
	{
		r = lua_tointeger(L, -1); lua_pop(L, 1);
		lua_getfield(L, idx, "g"); g = lua_tointeger(L, -1); lua_pop(L, 1);
		lua_getfield(L, idx, "b"); b = lua_tointeger(L, -1); lua_pop(L, 1);
	}

	return (SDL_Color) { r, g, b };
}


/* Convert a SDL_PixelFormat to LUA */
static void get_format(lua_State *L, SDL_PixelFormat* fmt)
{
	lua_newtable(L);
	luaL_getmetatable(L, "SDL.Format");
	lua_setmetatable(L, -2);

	lua_pushlightuserdata(L, fmt);
	lua_setfield(L, -2, "c_data");

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

	// palette - TODO
//	lua_newtable(L);
//	lua_setfield(L, -2, "palette");
}


/* update information on a SDL_Surface */
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

	rect(L, sf->clip_rect);
	lua_setfield(L, -2, "clip_rect");

	// pixels
	lua_newtable(L);
	luaL_getmetatable(L, "SDL.Pixel");
	lua_setmetatable(L, -2);
	lua_setfield(L, -2, "pixels");
	lua_getfield(L, -1, "pixels");
	lua_pushlightuserdata(L, sf->pixels);
	lua_setfield(L, -2, "c_data");
	lua_pop(L, 1);
}


/* create a LUA surface from a SDL_Surface */
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

/*
 *
 * SDL INITIALIZATION
 *
 */
static int Init(lua_State *L)
{
	Uint32 flags;
	if(check_args(L, 0, 1) == 0)
		flags = SDL_INIT_EVERYTHING;
	else
		flags = luaL_checklong(L, 1);

	int ok = (SDL_Init(flags) != -1);
	if(IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF) == 0)
		ok = 0;

	lua_pushboolean(L, ok);
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
	// TODO - IMG_GetError
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


/* 
 *
 * SDL VIDEO
 *
 */
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


static int ListModes(lua_State *L)
{
	check_args(L, 2, 2);

	SDL_PixelFormat* fmt = convert_format(L, 1);
	Uint32 flags = luaL_checklong(L, 2);

	SDL_Rect** n = SDL_ListModes(fmt, flags);
	if(n == (SDL_Rect**)0)
		lua_newtable(L);
	else if(n == (SDL_Rect**)-1)
		lua_pushnil(L);
	else
	{
		lua_newtable(L);

		int i;
		for (i=0; n[i]; ++i)
		{
			rect(L, *n[i]);
			lua_rawseti(L, -2, i+1);
		}
	}
	return 1;
}


static int VideoModeOK(lua_State *L)
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

	lua_pushinteger(L, SDL_VideoModeOK(w, h, bpp, flags));
	return 1;
}


static int SetGamma(lua_State *L)
{
	check_args(L, 3, 3);
	float r = luaL_checknumber(L, 1),
	      g = luaL_checknumber(L, 2),
	      b = luaL_checknumber(L, 3);
	lua_pushboolean(L, !SDL_SetGamma(r, g, b));
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
	if(nargs > 4) r = luaL_checklong(L, 5);
	if(nargs > 5) g = luaL_checklong(L, 6);
	if(nargs > 6) b = luaL_checklong(L, 7);
	if(nargs > 7) a = luaL_checklong(L, 8);

	SDL_Surface* sf = SDL_CreateRGBSurface(flags, w, h, bpp, r, g, b, a);
	if(!sf)
		lua_pushnil(L);
	else
		create_sf(L, sf);
	return 1;
}


static int Blit(lua_State *L)
{
	check_args(L, 4, 4);
	SDL_Surface *src = convert_surface(L, 1),
		    *dst = convert_surface(L, 3);
	SDL_Rect *sr = NULL, *dr = NULL;
	if(lua_isnil(L, 2))
		sr = NULL;
	else
		*sr = convert_rect(L, 2);
	if(lua_isnil(L, 4))
		dr = NULL;
	else
		*dr = convert_rect(L, 4);

	lua_pushboolean(L, !SDL_BlitSurface(src, sr, dst, dr));
	return 1;
}


/*
 *
 * SDL SURFACE
 *
 */
static int UpdateRect(lua_State *L)
{
	int nargs = check_args(L, 1, 2);
	SDL_Surface* sf = convert_surface(L, 1);
	SDL_Rect r = { 0, 0, 0, 0 };
	if(nargs == 2)
		r = convert_rect(L, 2);

	SDL_UpdateRect(sf, r.x, r.y, r.h, r.w);
	return 0;
}


static int UpdateRects(lua_State *L)
{
	check_args(L, 2, 2);
	SDL_Surface* sf = convert_surface(L, 1);

	int len = lua_objlen(L, 2);
	SDL_Rect* rects = malloc(sizeof(SDL_Rect) * len);

	int i;
	for(i=0; i<len; i++)
	{
		lua_rawgeti(L, 2, i+1);
		SDL_Rect r = convert_rect(L, -1);
		memcpy(&rects[i], &r, sizeof(SDL_Rect));
		lua_pop(L, 1);
	}
	SDL_UpdateRects(sf, len, rects);
	free(rects);

	return 0;
}


static int Flip(lua_State *L)
{
	check_args(L, 1, 1);
	SDL_Surface* sf = convert_surface(L, 1);
	lua_pushboolean(L, !SDL_Flip(sf));
	return 1;
}


static int SetColors(lua_State *L)
{
	check_args(L, 3, 3);
	SDL_Surface* sf = convert_surface(L, 1);
	int n_colors = lua_objlen(L, 2);
	int initial = luaL_checkinteger(L, 3);

	SDL_Color* colors = malloc(sizeof(SDL_Rect) * n_colors);

	int i;
	for(i=0; i<n_colors; i++)
	{
		lua_rawgeti(L, 2, i+1);
		SDL_Color c = convert_color(L, -1);
		memcpy(&colors[i], &c, sizeof(SDL_Color));
		lua_pop(L, 1);
	}
	lua_pushboolean(L, SDL_SetColors(sf, colors, initial, n_colors));
	free(colors);

	return 1;
}


static int SetPalette(lua_State *L)
{
	check_args(L, 4, 4);
	SDL_Surface* sf = convert_surface(L, 1);
	int flags = luaL_checkinteger(L, 2);
	int n_colors = lua_objlen(L, 3);
	int initial = luaL_checkinteger(L, 4);

	SDL_Color* colors = malloc(sizeof(SDL_Rect) * n_colors);

	int i;
	for(i=0; i<n_colors; i++)
	{
		lua_rawgeti(L, 3, i+1);
		SDL_Color c = convert_color(L, -1);
		memcpy(&colors[i], &c, sizeof(SDL_Color));
		lua_pop(L, 1);
	}
	lua_pushboolean(L, SDL_SetPalette(sf, flags, colors, initial, n_colors));
	free(colors);

	return 1;
}


static int Lock(lua_State *L)
{
	check_args(L, 1, 1);
	SDL_Surface* sf = convert_surface(L, 1);
	lua_pushboolean(L, !SDL_LockSurface(sf));
	return 1;
}


static int Unlock(lua_State *L)
{
	check_args(L, 1, 1);
	SDL_Surface* sf = convert_surface(L, 1);
	SDL_UnlockSurface(sf);
	return 0;
}


static int Free(lua_State *L)
{
	check_args(L, 1, 1);
	SDL_Surface* sf = convert_surface(L, 1);
	SDL_FreeSurface(sf);
	return 0;
}


static int Convert(lua_State *L)
{
	check_args(L, 3, 3);
	SDL_Surface* sf = convert_surface(L, 1);
	SDL_PixelFormat* fmt = convert_format(L, 2);
	Uint32 flags = luaL_checklong(L, 3);

	SDL_Surface* sf2 = SDL_ConvertSurface(sf, fmt, flags);
	if(!sf2)
		lua_pushnil(L);
	else
		create_sf(L, sf2);
	return 1;
}


static int DisplayFormat(lua_State *L)
{
	check_args(L, 1, 1);
	SDL_Surface* sf = convert_surface(L, 1);
	SDL_Surface* sf2 = SDL_DisplayFormat(sf);
	if(!sf2)
		lua_pushnil(L);
	else
		create_sf(L, sf2);
	return 1;
}


static int DisplayFormatAlpha(lua_State *L)
{
	check_args(L, 1, 1);
	SDL_Surface* sf = convert_surface(L, 1);
	SDL_Surface* sf2 = SDL_DisplayFormatAlpha(sf);
	if(!sf2)
		lua_pushnil(L);
	else
		create_sf(L, sf2);
	return 1;
}


static int SetColorKey(lua_State *L)
{
	check_args(L, 3, 3);
	SDL_Surface* sf = convert_surface(L, 1);
	Uint32 flag = luaL_checklong(L, 2),
	       key  = luaL_checklong(L, 3);
	lua_pushboolean(L, !SDL_SetColorKey(sf, flag, key));
	return 1;
}


static int SetAlpha(lua_State *L)
{
	check_args(L, 3, 3);
	SDL_Surface* sf = convert_surface(L, 1);
	Uint32 flag = luaL_checklong(L, 2);
	Uint8 alpha = luaL_checkinteger(L, 3);
	lua_pushboolean(L, !SDL_SetAlpha(sf, flag, alpha));
	return 1;
}


static int SetClipRect(lua_State *L)
{
	check_args(L, 2, 2);
	SDL_Surface* sf = convert_surface(L, 1);
	SDL_Rect r = convert_rect(L, 2);
	SDL_SetClipRect(sf, &r);
	return 0;
}


static int GetClipRect(lua_State *L)
{
	check_args(L, 1, 1);
	SDL_Surface* sf = convert_surface(L, 1);
	SDL_Rect r;
	SDL_GetClipRect(sf, &r);
	rect(L, r);
	return 1;
}


static int FillRect(lua_State *L)
{
	check_args(L, 3, 3);
	SDL_Surface* sf = convert_surface(L, 1);
	Uint32 color = luaL_checklong(L, 3);
	if(lua_isnil(L, 2))
		lua_pushboolean(L, !SDL_FillRect(sf, NULL, color));
	else
	{
		SDL_Rect r = convert_rect(L, 2);
		lua_pushboolean(L, !SDL_FillRect(sf, &r, color));
	}
	
	return 1;
}


/*
 *
 * SDL FORMAT
 *
 */
static int MapRGB(lua_State *L)
{
	int nargs = check_args(L, 4, 5);
	SDL_PixelFormat* fmt = convert_format(L, 1);
	int r = luaL_checkinteger(L, 2),
	    g = luaL_checkinteger(L, 3),
	    b = luaL_checkinteger(L, 4);
	if(nargs == 5)
	{
		int a = luaL_checkinteger(L, 5);
		lua_pushinteger(L, SDL_MapRGBA(fmt, r, g, b, a));
	}
	else
		lua_pushinteger(L, SDL_MapRGB(fmt, r, g, b));
	return 1;
}


static int GetRGB(lua_State *L)
{
	check_args(L, 2, 2);
	SDL_PixelFormat* fmt = convert_format(L, 1);
	int pixel = luaL_checkinteger(L, 2);

	Uint8 r, g, b, a;
	SDL_GetRGBA(pixel, fmt, &r, &g, &b, &a);

	int i = 1;
	lua_newtable(L);
	lua_pushinteger(L, r); lua_rawseti(L, -2, i++);
	lua_pushinteger(L, g); lua_rawseti(L, -2, i++);
	lua_pushinteger(L, b); lua_rawseti(L, -2, i++);
	lua_pushinteger(L, a); lua_rawseti(L, -2, i++);
	return 1;
}


/*
 *
 * SDL PIXEL DIRECT ACCESS
 *
 */
static int setpixel(lua_State *L)
{
	lua_getfield(L, 1, "c_data");
	void* pixels = lua_touserdata(L, -1);
	lua_pop(L, 1);

	int idx = luaL_checkint(L, 2);
	luaL_argcheck(L, idx >= 0, 2, "index out of range");
	
	int v = luaL_checkint(L, 3);
	luaL_argcheck(L, idx >= 0 && idx <= 255, 3, "byte must be between 0 and 255");

	((Uint8*)pixels)[idx] = v;
	return 0;
}


static int getpixel(lua_State *L)
{
	lua_getfield(L, 1, "c_data");
	void* pixels = lua_touserdata(L, -1);
	lua_pop(L, 1);

	int idx = luaL_checkint(L, 2);
	luaL_argcheck(L, idx >= 0, 2, "index out of range");

	lua_pushinteger(L, ((Uint8*)pixels)[idx]);
	return 1;
}


/*
 *
 * SDL WM MANAGEMENT
 *
 */
static int WM_SetCaption(lua_State *L)
{
	int nargs = check_args(L, 1, 2);
	const char *icon, *title = luaL_checkstring(L, 1);
	if(nargs == 2)
		icon = luaL_checkstring(L, 2);
	else
		icon = title;
	SDL_WM_SetCaption(title, icon);
	return 0;
}


static int WM_GetCaption(lua_State *L)
{
	check_args(L, 0, 0);
	char *title, *icon;
	SDL_WM_GetCaption(&title, &icon);

	lua_newtable(L);
	lua_pushstring(L, title); lua_rawseti(L, -2, 1);
	lua_pushstring(L, icon); lua_rawseti(L, -2, 2);
	return 1;
}


static int WM_SetIcon(lua_State *L)
{
	check_args(L, 1, 1);
	SDL_Surface* sf = convert_surface(L, 1);
	SDL_WM_SetIcon(sf, NULL);
	return 0;
}


static int WM_IconifyWindow(lua_State *L)
{
	check_args(L, 0, 0);
	lua_pushboolean(L, !SDL_WM_IconifyWindow());
	return 1;
}


static int WM_ToggleFullScreen(lua_State *L)
{
	check_args(L, 1, 1);
	SDL_Surface* sf = convert_surface(L, 1);
	lua_pushboolean(L, !SDL_WM_ToggleFullScreen(sf));
	return 1;
}


static int WM_GrabInput(lua_State *L)
{
	check_args(L, 1, 1);
	int mode = luaL_checkinteger(L, 1);
	lua_pushinteger(L, SDL_WM_GrabInput(mode));
	return 1;
}


/*
 *
 * SDL EVENTS
 *
 */
static void convert_event(lua_State *L, SDL_Event *e)
{
	lua_newtable(L);

	lua_pushinteger(L, e->type); lua_setfield(L, -2, "type");

	switch(e->type)
	{
	case SDL_ACTIVEEVENT:
		lua_pushboolean(L, e->active.gain); lua_setfield(L, -2, "gain");
		lua_pushinteger(L, e->active.state); lua_setfield(L, -2, "state");
		break;
	case SDL_KEYUP:
	case SDL_KEYDOWN:
		lua_pushinteger(L, e->key.state); lua_setfield(L, -2, "state");
		lua_pushinteger(L, e->key.keysym.scancode); lua_setfield(L, -2, "scancode");
		lua_pushinteger(L, e->key.keysym.sym); lua_setfield(L, -2, "sym");
		lua_pushinteger(L, e->key.keysym.mod); lua_setfield(L, -2, "mod");
		lua_pushinteger(L, e->key.keysym.unicode); lua_setfield(L, -2, "unicode");
		break;
	case SDL_MOUSEMOTION:
		lua_pushinteger(L, e->motion.state); lua_setfield(L, -2, "state");
		lua_pushinteger(L, e->motion.x); lua_setfield(L, -2, "x");
		lua_pushinteger(L, e->motion.y); lua_setfield(L, -2, "y");
		lua_pushinteger(L, e->motion.xrel); lua_setfield(L, -2, "xrel");
		lua_pushinteger(L, e->motion.yrel); lua_setfield(L, -2, "yrel");
		break;
	case SDL_MOUSEBUTTONUP:
	case SDL_MOUSEBUTTONDOWN:
		lua_pushinteger(L, e->button.which); lua_setfield(L, -2, "which");
		lua_pushinteger(L, e->button.button); lua_setfield(L, -2, "button");
		lua_pushinteger(L, e->button.state); lua_setfield(L, -2, "state");
		lua_pushinteger(L, e->button.x); lua_setfield(L, -2, "x");
		lua_pushinteger(L, e->button.y); lua_setfield(L, -2, "y");
		break;
	case SDL_JOYAXISMOTION:
		lua_pushinteger(L, e->jaxis.which); lua_setfield(L, -2, "which");
		lua_pushinteger(L, e->jaxis.axis); lua_setfield(L, -2, "axis");
		lua_pushinteger(L, e->jaxis.value); lua_setfield(L, -2, "value");
		break;
	case SDL_JOYBALLMOTION:
		lua_pushinteger(L, e->jball.which); lua_setfield(L, -2, "which");
		lua_pushinteger(L, e->jball.ball); lua_setfield(L, -2, "ball");
		lua_pushinteger(L, e->jball.xrel); lua_setfield(L, -2, "xrel");
		lua_pushinteger(L, e->jball.yrel); lua_setfield(L, -2, "yrel");
		break;
	case SDL_JOYHATMOTION:
		lua_pushinteger(L, e->jhat.which); lua_setfield(L, -2, "which");
		lua_pushinteger(L, e->jhat.hat); lua_setfield(L, -2, "hat");
		lua_pushinteger(L, e->jhat.value); lua_setfield(L, -2, "value");
		break;
	case SDL_JOYBUTTONUP:
	case SDL_JOYBUTTONDOWN:
		lua_pushinteger(L, e->jbutton.which); lua_setfield(L, -2, "which");
		lua_pushinteger(L, e->jbutton.button); lua_setfield(L, -2, "button");
		lua_pushinteger(L, e->jbutton.state); lua_setfield(L, -2, "state");
		break;
	case SDL_VIDEORESIZE:
		lua_pushinteger(L, e->resize.w); lua_setfield(L, -2, "w");
		lua_pushinteger(L, e->resize.h); lua_setfield(L, -2, "h");
		break;
	case SDL_USEREVENT:
		// TODO
		break;
	case SDL_SYSWMEVENT: // TODO - not implemented
		break;
	}
}


static int PumpEvents(lua_State *L)
{
	check_args(L, 0, 0);
	SDL_PumpEvents();
	return 0;
}


static int WaitEvent(lua_State *L)
{
	check_args(L, 0, 0);
	SDL_Event e;
	if(SDL_WaitEvent(&e))
		convert_event(L, &e);
	else
		lua_pushnil(L);
	return 1;
}


static int PollEvent(lua_State *L)
{
	check_args(L, 0, 0);
	SDL_Event e;
	if(SDL_PollEvent(&e))
		convert_event(L, &e);
	else
		lua_pushnil(L);
	return 1;
}


static int EventState(lua_State *L)
{
	check_args(L, 2, 2);
	Uint8 type = luaL_checkinteger(L, 1);
	int state = luaL_checkinteger(L, 2);
	lua_pushinteger(L, SDL_EventState(type, state));
	return 1;
}


/*
 *
 * SDL TIME
 *
 */
static int GetTicks(lua_State *L)
{
	check_args(L, 0, 0);
	lua_pushinteger(L, SDL_GetTicks());
	return 1;
}


static int Delay(lua_State *L)
{
	check_args(L, 1, 1);
	Uint32 ms = luaL_checkinteger(L, 1);
	SDL_Delay(ms);
	return 0;
}


/*
 *
 * SDL_IMAGE
 *
 */
static int _IMG_Load(lua_State *L)
{
	check_args(L, 1, 1);
	const char *file = luaL_checkstring(L, 1);
	SDL_Surface *sf = IMG_Load(file);
	if(!sf)
		lua_pushnil(L);
	else
		create_sf(L, sf);
	return 1;
}


/*
 *
 * LUA INITIALIZATION
 *
 */
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
	{ "ListModes", ListModes },
	{ "VideoModeOK", VideoModeOK },
	{ "SetGamma", SetGamma },
	{ "CreateRGBSurface", CreateRGBSurface },
	{ "Blit", Blit },

	{ "WM_SetCaption", WM_SetCaption },
	{ "WM_GetCaption", WM_GetCaption },
	{ "WM_SetIcon", WM_SetIcon },
	{ "WM_IconifyWindow", WM_IconifyWindow },
	{ "WM_ToggleFullScreen", WM_ToggleFullScreen },
	{ "WM_GrabInput", WM_GrabInput },

	{ "PumpEvents", PumpEvents },
	{ "PollEvent", PollEvent },
	{ "WaitEvent", WaitEvent },
	{ "EventState", EventState },

	{ "GetTicks", GetTicks },
	{ "Delay", Delay },

	{ "IMG_Load", _IMG_Load },

	{NULL, NULL}
};


static const struct luaL_reg SDL_Sf[] = {
	{ "UpdateRect", UpdateRect },
	{ "UpdateRects", UpdateRects },
	{ "Flip", Flip },
	{ "SetColors", SetColors },
	{ "SetPalette", SetPalette },
	{ "Lock", Lock },
	{ "Unlock", Unlock },
	{ "Free", Free },
	{ "Convert", Convert },
	{ "DisplayFormat", DisplayFormat },
	{ "DisplayFormatAlpha", DisplayFormatAlpha },
	{ "SetColorKey", SetColorKey },
	{ "SetAlpha", SetAlpha },
	{ "SetClipRect", SetClipRect },
	{ "GetClipRect", GetClipRect },
	{ "Blit", Blit },
	{ "FillRect", FillRect },
	{ NULL, NULL },
};


static const struct luaL_reg SDL_Format[] = {
	{ "MapRGB", MapRGB },
	{ "MapRGBA", MapRGB },
	{ "GetRGB", GetRGB },
	{ "GetRGBA", GetRGB },
	{ NULL, NULL }
};


static const struct luaL_reg SDL_Pixel[] = {
	{ "set", setpixel },
	{ "get", getpixel },
	{ NULL, NULL },
};


int luaopen_luasdl(lua_State *L)
{
	luaL_newmetatable(L, "SDL.Pixel");
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_register(L, NULL, SDL_Pixel);

	luaL_newmetatable(L, "SDL.Surface");
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_register(L, NULL, SDL_Sf);
	lua_pop(L, 2);

	luaL_newmetatable(L, "SDL.Format");
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_register(L, NULL, SDL_Format);
	lua_pop(L, 2);

	luaL_register(L, "SDL", SDL);
	init_constants(L);

	return 1;
}
