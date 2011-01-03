#include <stdlib.h>
#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "SDL.h"
#include "SDL_image.h"

#define SET_FUNCTION(table, name, function) { 	\
	lua_getglobal(L, table);		\
	lua_pushstring(L, name);		\
	lua_pushcfunction(L, function);		\
	lua_settable(L, -3);			\
}

typedef struct {
	int tile_w; 
	int tile_h;
	int w, h;
	SDL_Surface* scr;
	unsigned char* layer[3];
	SDL_Surface* image[3][256];
} Tileset;
static const char* last_image = "";
SDL_Surface* last_sf = NULL;


inline static Tileset* get_ts(lua_State* L)
{
	lua_getglobal(L, "self");
	lua_getfield(L, -1, "data");
	return lua_touserdata(L, -1);
}


// Tileset.get_event()
static int Tileset_get_event(lua_State* L)
{
	int err;
	SDL_Event e;
event:	SDL_WaitEvent(&e);
	if(e.type == SDL_KEYDOWN)
	{
		static struct {
			SDLKey key;
			const char* desc;
		} special[] = {
			{ SDLK_UP, 	"up" },
			{ SDLK_DOWN, 	"down" },
			{ SDLK_LEFT, 	"left" },
			{ SDLK_RIGHT, 	"right" },
			{ SDLK_KP0, 	"kp_0" },
			{ SDLK_KP1, 	"kp_1" },
			{ SDLK_KP2, 	"kp_2" },
			{ SDLK_KP3, 	"kp_3" },
			{ SDLK_KP4, 	"kp_4" },
			{ SDLK_KP5, 	"kp_5" },
			{ SDLK_KP6, 	"kp_6" },
			{ SDLK_KP7, 	"kp_7" },
			{ SDLK_KP8, 	"kp_8" },
			{ SDLK_KP9, 	"kp_9" },
			{ SDLK_KP_ENTER,"return" },
			{ SDLK_RETURN, 	"return" },
			{ 0, NULL }
		};

		char buf[1024] = "";
		int i = 0, found = 0;
		while(special[i].key != 0)
		{
			if(e.key.keysym.sym == special[i].key)
			{
				snprintf(buf, 1024, 
					"return { type = 'key', key = '%s', "
					"ascii = %d }",
					special[i].desc, e.key.keysym.sym);
				found = 1;
			}
			i++;
		}
		if(!found)	
			snprintf(buf, 1024, 
				"return { type = 'key', key = '%c', ascii = %d }",
				e.key.keysym.sym, e.key.keysym.sym);
		err = luaL_dostring(L, buf);
	}
	else if(e.type == SDL_QUIT)
	{
		err = luaL_dostring(L, "return { type = 'quit' }");
	}
	else
		goto event;

	if(err)
	{
		fprintf(stderr, "%s", lua_tostring(L, -1));
		exit(1);
	}

	return 1;
}


// Tileset.update()
static int Tileset_h(lua_State* L)
{
	Tileset* ts = get_ts(L);

	int h = ts->scr->h / ts->tile_h;
	lua_pushinteger(L, h);

	return 1;
}


// Tileset.update()
static int Tileset_update(lua_State* L)
{
	Tileset* ts = get_ts(L);

	SDL_FillRect(ts->scr, NULL, SDL_MapRGB(ts->scr->format, 0, 0, 0));

	int i, x, y;
	for(i=0; i<3; i++)
		for(x=0; x<ts->w; x++)
			for(y=0; y<ts->h; y++)
			{
				unsigned char c = ts->layer[i][x+(y*ts->w)];
				SDL_Rect r = { x * ts->tile_w,
			                       y * ts->tile_h };
				if(i == 0 || (i != 0 && c != ' '))
					SDL_BlitSurface(ts->image[i][c], NULL, 
							ts->scr, &r);
			}
	SDL_Flip(ts->scr);
	return 0;
}


// Tileset.set_char(layer, char, x, y)
static int Tileset_set_char(lua_State* L)
{
	// parameters
	int layer = luaL_checknumber(L, 1);
	int x = luaL_checknumber(L, 3);
	int y = luaL_checknumber(L, 4);
	unsigned char ch;
	if(lua_isnumber(L, 2))
		ch = (unsigned char)lua_tonumber(L, 2);
	else
		ch = (unsigned char)(luaL_checkstring(L, 2)[0]);

	Tileset* ts = get_ts(L);

	// checks
	if(layer < 0 || layer > 2)
		luaL_error(L, "Layer must be between 0 and 2");
	if(x < 0 || x >= ts->w)
		luaL_error(L, "X must be between 0 and %d", ts->w);
	if(y < 0 || y >= ts->h)
		luaL_error(L, "Y must be between 0 and %d", ts->h);

	// do
	ts->layer[layer][x + (y * ts->w)] = ch;

	// change cursor position
	char buf[150];
	sprintf(buf, "self.cursor.x = %d", x);
	if(luaL_dostring(L, buf) != 0)
		abort();
	sprintf(buf, "self.cursor.y = %d", y);
	if(luaL_dostring(L, buf) != 0)
		abort();

	return 0;
}

// Tileset.load_image(layer, char, image, x, y)
static int Tileset_load_image(lua_State* L)
{
	// parameters
	int layer = luaL_checknumber(L, 1);
	const char* image = luaL_checkstring(L, 3);
	int x = luaL_checknumber(L, 4);
	int y = luaL_checknumber(L, 5);
	unsigned char ch;
	if(lua_isnumber(L, 2))
		ch = (unsigned char)lua_tonumber(L, 2);
	else
		ch = (unsigned char)(luaL_checkstring(L, 2)[0]);

	Tileset* ts = get_ts(L);

	// checks
	if(layer < 0 || layer > 2)
		luaL_error(L, "Layer must be between 0 and 2");

	// load image
	SDL_Surface* sf2;
	if(strcmp(last_image, image) == 0)
	{
		sf2 = last_sf;
	}
	else
	{
		SDL_Surface* sf = IMG_Load(image);
		sf2 = SDL_DisplayFormat(sf);
		//sf2 = SDL_ConvertSurface(sf, ts->scr->format, SDL_SWSURFACE|SDL_SRCALPHA);
		if(!sf)
			luaL_error(L, "Invalid image file '%s'.", image);
		SDL_FreeSurface(sf);

		if(last_sf != NULL)
			SDL_FreeSurface(last_sf);
		last_sf = sf2;
		last_image = image;
	}
	if(x + ts->tile_w > sf2->w || y + ts->tile_h > sf2->h)
		luaL_error(L, "X and Y can't be outside the image.");

	// create image
	ts->image[layer][ch] = SDL_CreateRGBSurface(
			SDL_SWSURFACE, 
			ts->tile_w, ts->tile_h, 32, 0, 0, 0, 0);
	//ts->image[layer][ch] = SDL_DisplayFormat(ts->image[layer][ch]);
	//if(layer==0)
	SDL_SetColorKey(ts->image[layer][ch], SDL_SRCCOLORKEY, SDL_MapRGB(ts->image[layer][ch]->format, 0, 0, 0));
	SDL_BlitSurface(sf2, &(SDL_Rect) { x, y, ts->tile_w, ts->tile_h },
			ts->image[layer][ch], NULL);

	return 0;
}

static int Tileset_new(lua_State* L)
{
	int w = luaL_checknumber(L, 1);
	int h = luaL_checknumber(L, 2);

	// self = {}
	//lua_newtable(L);
	lua_getglobal(L, "AbstractTileset");
	lua_setglobal(L, "self");

	// self.data
	lua_getglobal(L, "self");
	lua_pushstring(L, "data");
	Tileset* ts = (Tileset*)lua_newuserdata(L, sizeof(Tileset));
	lua_settable(L, -3);
	ts->tile_w = w;
	ts->tile_h = h;

	// functions
	SET_FUNCTION("self", "set_char", Tileset_set_char);
	SET_FUNCTION("self", "load_image", Tileset_load_image);
	SET_FUNCTION("self", "update", Tileset_update);
	SET_FUNCTION("self", "get_event", Tileset_get_event);
	SET_FUNCTION("self", "h", Tileset_h);

	// initialize scr
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	ts->w = 80; ts->h = 50;
	ts->scr = SDL_SetVideoMode(ts->w * ts->tile_w, ts->h * ts->tile_h,
			32, SDL_SWSURFACE);

	// initialize layers
	int i, j;
	SDL_Surface* blank = SDL_CreateRGBSurface(SDL_SWSURFACE, 
			ts->tile_w, ts->tile_h, 32, 0, 0, 0, 0);
	SDL_SetColorKey(blank, SDL_SRCCOLORKEY, 0);
	for(i=0; i<3; i++)
	{
		ts->layer[i] = malloc(ts->w * ts->h);
		for(j=0; j<(ts->w * ts->h); j++)
			ts->layer[i][j] = ' ';
		for(j=0; j<256; j++)
			ts->image[i][j] = blank;
	}

	// return self
	lua_getglobal(L, "self");
	return 1;
}

int luaopen_libtileset(lua_State *L)
{
	// Tileset = {}
	lua_newtable(L);
	lua_setglobal(L, "Tileset");

	// function Tileset.new()
	SET_FUNCTION("Tileset", "new", Tileset_new);

	return 1;
}
