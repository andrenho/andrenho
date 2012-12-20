#ifndef RESOURCE_LIST_H
#define RESOURCE_LIST_H

#include "SDL.h"

// terrain tiles
SDL_Rect terrain_r[] = {
	{  0, 160, 32, 32 }, { 32, 160, 32, 32 }, { 64, 160, 32, 32 },
	{ 32,   0, 32, 32 }, { 64,   0, 32, 32 }, { 32,  32, 32, 32 }, 
	{ 64,  32, 32, 32 }, {  0,  64, 32, 32 }, { 32,  64, 32, 32 },
	{ 64,  64, 32, 32 }, {  0,  96, 32, 32 }, { 32,  96, 32, 32 },
	{ 64,  96, 32, 32 }, {  0, 128, 32, 32 }, { 32, 128, 32, 32 },
	{ 64, 128, 32, 32 }, {  0,   0, 32, 32 }, { 32,   0, 32, 32 },
};
char* terrain_sfx[] = { 
	"_1", "_2", "_3",
	"_ic_nw", "_ic_ne", "_ic_sw", 
	"_ic_se", "_ec_nw", "_ec_n", 
	"_ec_ne", "_ec_w", "", 
	"_ec_e", "_ec_sw", "_ec_s",
	"_ec_se", "_s_1", "_s_2", NULL
};

// resource files list
static struct { 
	char name[RES_CHARS];
	char *filename;
	SDL_Rect* r; // list of rectangles
	char **suffix;
} reslist[] = {
	{ "grass",     "grass.png",     terrain_r, terrain_sfx },
	{ "grassalt",  "grassalt.png",  terrain_r, terrain_sfx },
	{ "dirt",      "dirt.png",      terrain_r, terrain_sfx },
	{ "earth",     "dirt2.png",     terrain_r, terrain_sfx },
	{ "lava",      "lava.png",      terrain_r, terrain_sfx },
	{ "lavarock",  "lavarock.png",  terrain_r, terrain_sfx },
	{ "water",     "water.png",     terrain_r, terrain_sfx },
	{ "watergrass","watergrass.png",terrain_r, terrain_sfx },
	{ "snow",      "snow.png",      terrain_r, terrain_sfx },
	{ "\0", NULL, NULL, NULL }
};

#endif
