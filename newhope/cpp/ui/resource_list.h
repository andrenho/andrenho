#ifndef RESOURCE_LIST_H
#define RESOURCE_LIST_H

#include <string>
#include "libs/rect.h"

// single images
const Rect terrain_r[] = {
	Rect(  0, 160, 32, 32 ), Rect( 32, 160, 32, 32 ), Rect( 64, 160, 32, 32 ),
	Rect( 32,   0, 32, 32 ), Rect( 64,   0, 32, 32 ), Rect( 32,  32, 32, 32 ), 
	Rect( 64,  32, 32, 32 ), Rect(  0,  64, 32, 32 ), Rect( 32,  64, 32, 32 ),
	Rect( 64,  64, 32, 32 ), Rect(  0,  96, 32, 32 ), Rect( 32,  96, 32, 32 ),
	Rect( 64,  96, 32, 32 ), Rect(  0, 128, 32, 32 ), Rect( 32, 128, 32, 32 ),
	Rect( 64, 128, 32, 32 ), Rect(  0,   0, 32, 32 ), Rect( 32,   0, 32, 32 ),
};

const std::string terrain_sfx[] = { 
	"_1", "_2", "_3",
	"_ic_nw", "_ic_ne", "_ic_sw", 
	"_ic_se", "_ec_nw", "_ec_n", 
	"_ec_ne", "_ec_w", "", 
	"_ec_e", "_ec_sw", "_ec_s",
	"_ec_se", "_s_1", "_s_2", ""
};

// minimap tiles
const Rect mm_r[] = {
	Rect( 353, 128, 60, 67 ), Rect( 413, 128, 66, 67 ), Rect( 479, 128, 64, 67 ),
	Rect( 353, 195, 60, 59 ), Rect( 413, 195, 66, 59 ), Rect( 479, 195, 64, 59 ),
	Rect( 353, 254, 60, 65 ), Rect( 413, 254, 66, 65 ), Rect( 479, 254, 64, 65 ),
};
const std::string mm_sfx[] = { 
	"_nw", "_n", "_ne", "_w", "_c", "_e", "_sw", "_s", "_se", ""
};

// resource file list
static const struct {
	const std::string name;
	const std::string filename;
	const Rect *r;
	const std::string *suffix;
} reslist[] = {

	// terrains
	{ "grass",     "grass.png",     terrain_r, terrain_sfx },
	{ "grassalt",  "grassalt.png",  terrain_r, terrain_sfx },
	{ "dirt",      "dirt.png",      terrain_r, terrain_sfx },
	{ "earth",     "dirt2.png",     terrain_r, terrain_sfx },
	{ "lava",      "lava.png",      terrain_r, terrain_sfx },
	{ "lavarock",  "lavarock.png",  terrain_r, terrain_sfx },
	{ "water",     "water.png",     terrain_r, terrain_sfx },
	{ "watergrass","watergrass.png",terrain_r, terrain_sfx },
	{ "snow",      "snow.png",      terrain_r, terrain_sfx },

	// map
	{ "mm", "scrollsandblocks.png", mm_r, mm_sfx },

	// terminal
	{ "terminal", "terminal.png", 0, 0 },

	// fonts
//	Rect( "termfont", "Glass_TTY_VT220.ttf", (SDL_Rect[]) { { 20 ) }, 
//		(std::string[]) Rect( "_20", NULL ) },

	{ "", "", NULL, NULL }
};

#endif
