#ifndef RESOURCE_LIST_H
#define RESOURCE_LIST_H

#include <vector>
#include <string>
#include "util/rect.h"

using namespace std;

// single images
const vector<Rect> terrain_r = {
	Rect( 0, 160, 32, 32), Rect(32, 160, 32, 32), Rect(64, 160, 32, 32),
	Rect(32,   0, 32, 32), Rect(64,   0, 32, 32), Rect(32,  32, 32, 32), 
	Rect(64,  32, 32, 32), Rect( 0,  64, 32, 32), Rect(32,  64, 32, 32),
	Rect(64,  64, 32, 32), Rect( 0,  96, 32, 32), Rect(32,  96, 32, 32),
	Rect(64,  96, 32, 32), Rect( 0, 128, 32, 32), Rect(32, 128, 32, 32),
	Rect(64, 128, 32, 32), Rect( 0,   0, 32, 32), Rect(32,   0, 32, 32),
};

const vector<string> terrain_sfx { 
	"_0", "_1", "_2",
	"_ic_nw", "_ic_ne", "_ic_sw", 
	"_ic_se", "_ec_nw", "_ec_n", 
	"_ec_ne", "_ec_w", "_c", 
	"_ec_e", "_ec_sw", "_ec_s",
	"_ec_se", "_s_1", "_s_2"
};

// minimap tiles
const vector<Rect> mm_r {
	Rect(353, 128, 60, 67), Rect(413, 128, 66, 67), Rect(479, 128, 64, 67),
	Rect(353, 195, 60, 59), Rect(413, 195, 66, 59), Rect(479, 195, 64, 59),
	Rect(353, 254, 60, 65), Rect(413, 254, 66, 65), Rect(479, 254, 64, 65),
};
const vector<string> mm_sfx { 
	"_nw", "_n", "_ne", "_w", "_c", "_e", "_sw", "_s", "_se"
};

// character
const int dx = 17, dy = 15, dw=48-dx, dh=60-dy;
constexpr Rect cr(int x, int y) { return Rect(64*x+dx, 64*y+dy, dw, dh); }
const vector<Rect> char_rects {
	cr(0,0),cr(1,0),cr(2,0),cr(3,0),cr(4,0),cr(5,0),cr(6,0),cr(7,0),cr(8,0), 
	cr(0,1),cr(1,1),cr(2,1),cr(3,1),cr(4,1),cr(5,1),cr(6,1),cr(7,1),cr(8,1), 
	cr(0,2),cr(1,2),cr(2,2),cr(3,2),cr(4,2),cr(5,2),cr(6,2),cr(7,2),cr(8,2),
	cr(0,3),cr(1,3),cr(2,3),cr(3,3),cr(4,3),cr(5,3),cr(6,3),cr(7,3),cr(8,3)
};
const vector<string> char_sfx {
	"_n_0", "_n_1", "_n_2", "_n_3", "_n_4", "_n_5", "_n_6", "_n_7", "_n_8", 
	"_w_0", "_w_1", "_w_2", "_w_3", "_w_4", "_w_5", "_w_6", "_w_7", "_w_8",
	"_s_0", "_s_1", "_s_2", "_s_3", "_s_4", "_s_5", "_s_6", "_s_7", "_s_8", 
	"_e_0", "_e_1", "_e_2", "_e_3", "_e_4", "_e_5", "_e_6", "_e_7", "_e_8"
};

// resource file list
static const struct {
	const string name;
	const string filename;
	const vector<Rect> r;
	const vector<string> suffix;
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

	// trees
	{ "trunk", "trunk.png", { Rect(0,0,96,96), Rect(96,0,96,96) }, 
		{ "_1", "_2" } },

	// map
	{ "mm", "scrollsandblocks.png", mm_r, mm_sfx },

	// characters
	{ "male", "male_walkcycle.png", char_rects, char_sfx },
	{ "pants", "male_pants.png", char_rects, char_sfx },

	// terminal
	{ "terminal", "terminal.png", {}, {} },

	// fonts
	{ "termfont", "Glass_TTY_VT220.ttf", { Rect(20) }, { "_20" } },
};

#endif
