#include <libtcod.h>
#include <stdlib.h>
#include "uthash.h"
typedef struct { char name[50]; TCOD_color_t color; UT_hash_handle hh; } COLOR;

COLOR *colors = NULL;

void init_colors()
{
	COLOR *c;
	
	// red
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "red");
	c->color = TCOD_red;
	HASH_ADD_STR(colors, name, c);
	
	// flame
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "flame");
	c->color = TCOD_flame;
	HASH_ADD_STR(colors, name, c);
	
	// orange
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "orange");
	c->color = TCOD_orange;
	HASH_ADD_STR(colors, name, c);
	
	// amber
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "amber");
	c->color = TCOD_amber;
	HASH_ADD_STR(colors, name, c);
	
	// yellow
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "yellow");
	c->color = TCOD_yellow;
	HASH_ADD_STR(colors, name, c);
	
	// lime
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lime");
	c->color = TCOD_lime;
	HASH_ADD_STR(colors, name, c);
	
	// chartreuse
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "chartreuse");
	c->color = TCOD_chartreuse;
	HASH_ADD_STR(colors, name, c);
	
	// green
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "green");
	c->color = TCOD_green;
	HASH_ADD_STR(colors, name, c);
	
	// sea
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "sea");
	c->color = TCOD_sea;
	HASH_ADD_STR(colors, name, c);
	
	// turquoise
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "turquoise");
	c->color = TCOD_turquoise;
	HASH_ADD_STR(colors, name, c);
	
	// cyan
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "cyan");
	c->color = TCOD_cyan;
	HASH_ADD_STR(colors, name, c);
	
	// sky
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "sky");
	c->color = TCOD_sky;
	HASH_ADD_STR(colors, name, c);
	
	// azure
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "azure");
	c->color = TCOD_azure;
	HASH_ADD_STR(colors, name, c);
	
	// blue
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "blue");
	c->color = TCOD_blue;
	HASH_ADD_STR(colors, name, c);
	
	// han
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "han");
	c->color = TCOD_han;
	HASH_ADD_STR(colors, name, c);
	
	// violet
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "violet");
	c->color = TCOD_violet;
	HASH_ADD_STR(colors, name, c);
	
	// purple
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "purple");
	c->color = TCOD_purple;
	HASH_ADD_STR(colors, name, c);
	
	// fuchsia
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "fuchsia");
	c->color = TCOD_fuchsia;
	HASH_ADD_STR(colors, name, c);
	
	// magenta
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "magenta");
	c->color = TCOD_magenta;
	HASH_ADD_STR(colors, name, c);
	
	// pink
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "pink");
	c->color = TCOD_pink;
	HASH_ADD_STR(colors, name, c);
	
	// crimson
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "crimson");
	c->color = TCOD_crimson;
	HASH_ADD_STR(colors, name, c);
	
	// gray
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "gray");
	c->color = TCOD_gray;
	HASH_ADD_STR(colors, name, c);
	
	// sepia
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "sepia");
	c->color = TCOD_sepia;
	HASH_ADD_STR(colors, name, c);
	
	// brass
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "brass");
	c->color = TCOD_brass;
	HASH_ADD_STR(colors, name, c);
	
	// copper
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "copper");
	c->color = TCOD_copper;
	HASH_ADD_STR(colors, name, c);
	
	// gold
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "gold");
	c->color = TCOD_gold;
	HASH_ADD_STR(colors, name, c);
	
	// silver
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "silver");
	c->color = TCOD_silver;
	HASH_ADD_STR(colors, name, c);
	
	// celadon
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "celadon");
	c->color = TCOD_celadon;
	HASH_ADD_STR(colors, name, c);
	
	// peach
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "peach");
	c->color = TCOD_peach;
	HASH_ADD_STR(colors, name, c);
	
	// black
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "black");
	c->color = TCOD_black;
	HASH_ADD_STR(colors, name, c);
	
	// white
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "white");
	c->color = TCOD_white;
	HASH_ADD_STR(colors, name, c);
	
	// desaturated_red
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "desaturated_red");
	c->color = TCOD_desaturated_red;
	HASH_ADD_STR(colors, name, c);
	
	// lightest_red
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lightest_red");
	c->color = TCOD_lightest_red;
	HASH_ADD_STR(colors, name, c);
	
	// lighter_red
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lighter_red");
	c->color = TCOD_lighter_red;
	HASH_ADD_STR(colors, name, c);
	
	// light_red
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "light_red");
	c->color = TCOD_light_red;
	HASH_ADD_STR(colors, name, c);
	
	// dark_red
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "dark_red");
	c->color = TCOD_dark_red;
	HASH_ADD_STR(colors, name, c);
	
	// darker_red
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darker_red");
	c->color = TCOD_darker_red;
	HASH_ADD_STR(colors, name, c);
	
	// darkest_red
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darkest_red");
	c->color = TCOD_darkest_red;
	HASH_ADD_STR(colors, name, c);
	
	// desaturated_flame
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "desaturated_flame");
	c->color = TCOD_desaturated_flame;
	HASH_ADD_STR(colors, name, c);
	
	// lightest_flame
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lightest_flame");
	c->color = TCOD_lightest_flame;
	HASH_ADD_STR(colors, name, c);
	
	// lighter_flame
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lighter_flame");
	c->color = TCOD_lighter_flame;
	HASH_ADD_STR(colors, name, c);
	
	// light_flame
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "light_flame");
	c->color = TCOD_light_flame;
	HASH_ADD_STR(colors, name, c);
	
	// dark_flame
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "dark_flame");
	c->color = TCOD_dark_flame;
	HASH_ADD_STR(colors, name, c);
	
	// darker_flame
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darker_flame");
	c->color = TCOD_darker_flame;
	HASH_ADD_STR(colors, name, c);
	
	// darkest_flame
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darkest_flame");
	c->color = TCOD_darkest_flame;
	HASH_ADD_STR(colors, name, c);
	
	// desaturated_orange
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "desaturated_orange");
	c->color = TCOD_desaturated_orange;
	HASH_ADD_STR(colors, name, c);
	
	// lightest_orange
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lightest_orange");
	c->color = TCOD_lightest_orange;
	HASH_ADD_STR(colors, name, c);
	
	// lighter_orange
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lighter_orange");
	c->color = TCOD_lighter_orange;
	HASH_ADD_STR(colors, name, c);
	
	// light_orange
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "light_orange");
	c->color = TCOD_light_orange;
	HASH_ADD_STR(colors, name, c);
	
	// dark_orange
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "dark_orange");
	c->color = TCOD_dark_orange;
	HASH_ADD_STR(colors, name, c);
	
	// darker_orange
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darker_orange");
	c->color = TCOD_darker_orange;
	HASH_ADD_STR(colors, name, c);
	
	// darkest_orange
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darkest_orange");
	c->color = TCOD_darkest_orange;
	HASH_ADD_STR(colors, name, c);
	
	// desaturated_amber
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "desaturated_amber");
	c->color = TCOD_desaturated_amber;
	HASH_ADD_STR(colors, name, c);
	
	// lightest_amber
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lightest_amber");
	c->color = TCOD_lightest_amber;
	HASH_ADD_STR(colors, name, c);
	
	// lighter_amber
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lighter_amber");
	c->color = TCOD_lighter_amber;
	HASH_ADD_STR(colors, name, c);
	
	// light_amber
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "light_amber");
	c->color = TCOD_light_amber;
	HASH_ADD_STR(colors, name, c);
	
	// dark_amber
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "dark_amber");
	c->color = TCOD_dark_amber;
	HASH_ADD_STR(colors, name, c);
	
	// darker_amber
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darker_amber");
	c->color = TCOD_darker_amber;
	HASH_ADD_STR(colors, name, c);
	
	// darkest_amber
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darkest_amber");
	c->color = TCOD_darkest_amber;
	HASH_ADD_STR(colors, name, c);
	
	// desaturated_yellow
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "desaturated_yellow");
	c->color = TCOD_desaturated_yellow;
	HASH_ADD_STR(colors, name, c);
	
	// lightest_yellow
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lightest_yellow");
	c->color = TCOD_lightest_yellow;
	HASH_ADD_STR(colors, name, c);
	
	// lighter_yellow
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lighter_yellow");
	c->color = TCOD_lighter_yellow;
	HASH_ADD_STR(colors, name, c);
	
	// light_yellow
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "light_yellow");
	c->color = TCOD_light_yellow;
	HASH_ADD_STR(colors, name, c);
	
	// dark_yellow
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "dark_yellow");
	c->color = TCOD_dark_yellow;
	HASH_ADD_STR(colors, name, c);
	
	// darker_yellow
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darker_yellow");
	c->color = TCOD_darker_yellow;
	HASH_ADD_STR(colors, name, c);
	
	// darkest_yellow
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darkest_yellow");
	c->color = TCOD_darkest_yellow;
	HASH_ADD_STR(colors, name, c);
	
	// desaturated_lime
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "desaturated_lime");
	c->color = TCOD_desaturated_lime;
	HASH_ADD_STR(colors, name, c);
	
	// lightest_lime
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lightest_lime");
	c->color = TCOD_lightest_lime;
	HASH_ADD_STR(colors, name, c);
	
	// lighter_lime
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lighter_lime");
	c->color = TCOD_lighter_lime;
	HASH_ADD_STR(colors, name, c);
	
	// light_lime
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "light_lime");
	c->color = TCOD_light_lime;
	HASH_ADD_STR(colors, name, c);
	
	// dark_lime
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "dark_lime");
	c->color = TCOD_dark_lime;
	HASH_ADD_STR(colors, name, c);
	
	// darker_lime
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darker_lime");
	c->color = TCOD_darker_lime;
	HASH_ADD_STR(colors, name, c);
	
	// darkest_lime
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darkest_lime");
	c->color = TCOD_darkest_lime;
	HASH_ADD_STR(colors, name, c);
	
	// desaturated_chartreuse
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "desaturated_chartreuse");
	c->color = TCOD_desaturated_chartreuse;
	HASH_ADD_STR(colors, name, c);
	
	// lightest_chartreuse
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lightest_chartreuse");
	c->color = TCOD_lightest_chartreuse;
	HASH_ADD_STR(colors, name, c);
	
	// lighter_chartreuse
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lighter_chartreuse");
	c->color = TCOD_lighter_chartreuse;
	HASH_ADD_STR(colors, name, c);
	
	// light_chartreuse
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "light_chartreuse");
	c->color = TCOD_light_chartreuse;
	HASH_ADD_STR(colors, name, c);
	
	// dark_chartreuse
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "dark_chartreuse");
	c->color = TCOD_dark_chartreuse;
	HASH_ADD_STR(colors, name, c);
	
	// darker_chartreuse
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darker_chartreuse");
	c->color = TCOD_darker_chartreuse;
	HASH_ADD_STR(colors, name, c);
	
	// darkest_chartreuse
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darkest_chartreuse");
	c->color = TCOD_darkest_chartreuse;
	HASH_ADD_STR(colors, name, c);
	
	// desaturated_green
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "desaturated_green");
	c->color = TCOD_desaturated_green;
	HASH_ADD_STR(colors, name, c);
	
	// lightest_green
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lightest_green");
	c->color = TCOD_lightest_green;
	HASH_ADD_STR(colors, name, c);
	
	// lighter_green
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lighter_green");
	c->color = TCOD_lighter_green;
	HASH_ADD_STR(colors, name, c);
	
	// light_green
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "light_green");
	c->color = TCOD_light_green;
	HASH_ADD_STR(colors, name, c);
	
	// dark_green
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "dark_green");
	c->color = TCOD_dark_green;
	HASH_ADD_STR(colors, name, c);
	
	// darker_green
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darker_green");
	c->color = TCOD_darker_green;
	HASH_ADD_STR(colors, name, c);
	
	// darkest_green
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darkest_green");
	c->color = TCOD_darkest_green;
	HASH_ADD_STR(colors, name, c);
	
	// desaturated_sea
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "desaturated_sea");
	c->color = TCOD_desaturated_sea;
	HASH_ADD_STR(colors, name, c);
	
	// lightest_sea
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lightest_sea");
	c->color = TCOD_lightest_sea;
	HASH_ADD_STR(colors, name, c);
	
	// lighter_sea
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lighter_sea");
	c->color = TCOD_lighter_sea;
	HASH_ADD_STR(colors, name, c);
	
	// light_sea
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "light_sea");
	c->color = TCOD_light_sea;
	HASH_ADD_STR(colors, name, c);
	
	// dark_sea
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "dark_sea");
	c->color = TCOD_dark_sea;
	HASH_ADD_STR(colors, name, c);
	
	// darker_sea
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darker_sea");
	c->color = TCOD_darker_sea;
	HASH_ADD_STR(colors, name, c);
	
	// darkest_sea
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darkest_sea");
	c->color = TCOD_darkest_sea;
	HASH_ADD_STR(colors, name, c);
	
	// desaturated_turquoise
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "desaturated_turquoise");
	c->color = TCOD_desaturated_turquoise;
	HASH_ADD_STR(colors, name, c);
	
	// lightest_turquoise
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lightest_turquoise");
	c->color = TCOD_lightest_turquoise;
	HASH_ADD_STR(colors, name, c);
	
	// lighter_turquoise
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lighter_turquoise");
	c->color = TCOD_lighter_turquoise;
	HASH_ADD_STR(colors, name, c);
	
	// light_turquoise
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "light_turquoise");
	c->color = TCOD_light_turquoise;
	HASH_ADD_STR(colors, name, c);
	
	// dark_turquoise
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "dark_turquoise");
	c->color = TCOD_dark_turquoise;
	HASH_ADD_STR(colors, name, c);
	
	// darker_turquoise
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darker_turquoise");
	c->color = TCOD_darker_turquoise;
	HASH_ADD_STR(colors, name, c);
	
	// darkest_turquoise
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darkest_turquoise");
	c->color = TCOD_darkest_turquoise;
	HASH_ADD_STR(colors, name, c);
	
	// desaturated_cyan
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "desaturated_cyan");
	c->color = TCOD_desaturated_cyan;
	HASH_ADD_STR(colors, name, c);
	
	// lightest_cyan
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lightest_cyan");
	c->color = TCOD_lightest_cyan;
	HASH_ADD_STR(colors, name, c);
	
	// lighter_cyan
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lighter_cyan");
	c->color = TCOD_lighter_cyan;
	HASH_ADD_STR(colors, name, c);
	
	// light_cyan
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "light_cyan");
	c->color = TCOD_light_cyan;
	HASH_ADD_STR(colors, name, c);
	
	// dark_cyan
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "dark_cyan");
	c->color = TCOD_dark_cyan;
	HASH_ADD_STR(colors, name, c);
	
	// darker_cyan
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darker_cyan");
	c->color = TCOD_darker_cyan;
	HASH_ADD_STR(colors, name, c);
	
	// darkest_cyan
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darkest_cyan");
	c->color = TCOD_darkest_cyan;
	HASH_ADD_STR(colors, name, c);
	
	// desaturated_sky
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "desaturated_sky");
	c->color = TCOD_desaturated_sky;
	HASH_ADD_STR(colors, name, c);
	
	// lightest_sky
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lightest_sky");
	c->color = TCOD_lightest_sky;
	HASH_ADD_STR(colors, name, c);
	
	// lighter_sky
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lighter_sky");
	c->color = TCOD_lighter_sky;
	HASH_ADD_STR(colors, name, c);
	
	// light_sky
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "light_sky");
	c->color = TCOD_light_sky;
	HASH_ADD_STR(colors, name, c);
	
	// dark_sky
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "dark_sky");
	c->color = TCOD_dark_sky;
	HASH_ADD_STR(colors, name, c);
	
	// darker_sky
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darker_sky");
	c->color = TCOD_darker_sky;
	HASH_ADD_STR(colors, name, c);
	
	// darkest_sky
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darkest_sky");
	c->color = TCOD_darkest_sky;
	HASH_ADD_STR(colors, name, c);
	
	// desaturated_azure
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "desaturated_azure");
	c->color = TCOD_desaturated_azure;
	HASH_ADD_STR(colors, name, c);
	
	// lightest_azure
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lightest_azure");
	c->color = TCOD_lightest_azure;
	HASH_ADD_STR(colors, name, c);
	
	// lighter_azure
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lighter_azure");
	c->color = TCOD_lighter_azure;
	HASH_ADD_STR(colors, name, c);
	
	// light_azure
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "light_azure");
	c->color = TCOD_light_azure;
	HASH_ADD_STR(colors, name, c);
	
	// dark_azure
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "dark_azure");
	c->color = TCOD_dark_azure;
	HASH_ADD_STR(colors, name, c);
	
	// darker_azure
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darker_azure");
	c->color = TCOD_darker_azure;
	HASH_ADD_STR(colors, name, c);
	
	// darkest_azure
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darkest_azure");
	c->color = TCOD_darkest_azure;
	HASH_ADD_STR(colors, name, c);
	
	// desaturated_blue
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "desaturated_blue");
	c->color = TCOD_desaturated_blue;
	HASH_ADD_STR(colors, name, c);
	
	// lightest_blue
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lightest_blue");
	c->color = TCOD_lightest_blue;
	HASH_ADD_STR(colors, name, c);
	
	// lighter_blue
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lighter_blue");
	c->color = TCOD_lighter_blue;
	HASH_ADD_STR(colors, name, c);
	
	// light_blue
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "light_blue");
	c->color = TCOD_light_blue;
	HASH_ADD_STR(colors, name, c);
	
	// dark_blue
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "dark_blue");
	c->color = TCOD_dark_blue;
	HASH_ADD_STR(colors, name, c);
	
	// darker_blue
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darker_blue");
	c->color = TCOD_darker_blue;
	HASH_ADD_STR(colors, name, c);
	
	// darkest_blue
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darkest_blue");
	c->color = TCOD_darkest_blue;
	HASH_ADD_STR(colors, name, c);
	
	// desaturated_han
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "desaturated_han");
	c->color = TCOD_desaturated_han;
	HASH_ADD_STR(colors, name, c);
	
	// lightest_han
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lightest_han");
	c->color = TCOD_lightest_han;
	HASH_ADD_STR(colors, name, c);
	
	// lighter_han
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lighter_han");
	c->color = TCOD_lighter_han;
	HASH_ADD_STR(colors, name, c);
	
	// light_han
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "light_han");
	c->color = TCOD_light_han;
	HASH_ADD_STR(colors, name, c);
	
	// dark_han
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "dark_han");
	c->color = TCOD_dark_han;
	HASH_ADD_STR(colors, name, c);
	
	// darker_han
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darker_han");
	c->color = TCOD_darker_han;
	HASH_ADD_STR(colors, name, c);
	
	// darkest_han
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darkest_han");
	c->color = TCOD_darkest_han;
	HASH_ADD_STR(colors, name, c);
	
	// desaturated_violet
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "desaturated_violet");
	c->color = TCOD_desaturated_violet;
	HASH_ADD_STR(colors, name, c);
	
	// lightest_violet
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lightest_violet");
	c->color = TCOD_lightest_violet;
	HASH_ADD_STR(colors, name, c);
	
	// lighter_violet
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lighter_violet");
	c->color = TCOD_lighter_violet;
	HASH_ADD_STR(colors, name, c);
	
	// light_violet
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "light_violet");
	c->color = TCOD_light_violet;
	HASH_ADD_STR(colors, name, c);
	
	// dark_violet
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "dark_violet");
	c->color = TCOD_dark_violet;
	HASH_ADD_STR(colors, name, c);
	
	// darker_violet
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darker_violet");
	c->color = TCOD_darker_violet;
	HASH_ADD_STR(colors, name, c);
	
	// darkest_violet
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darkest_violet");
	c->color = TCOD_darkest_violet;
	HASH_ADD_STR(colors, name, c);
	
	// desaturated_purple
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "desaturated_purple");
	c->color = TCOD_desaturated_purple;
	HASH_ADD_STR(colors, name, c);
	
	// lightest_purple
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lightest_purple");
	c->color = TCOD_lightest_purple;
	HASH_ADD_STR(colors, name, c);
	
	// lighter_purple
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lighter_purple");
	c->color = TCOD_lighter_purple;
	HASH_ADD_STR(colors, name, c);
	
	// light_purple
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "light_purple");
	c->color = TCOD_light_purple;
	HASH_ADD_STR(colors, name, c);
	
	// dark_purple
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "dark_purple");
	c->color = TCOD_dark_purple;
	HASH_ADD_STR(colors, name, c);
	
	// darker_purple
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darker_purple");
	c->color = TCOD_darker_purple;
	HASH_ADD_STR(colors, name, c);
	
	// darkest_purple
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darkest_purple");
	c->color = TCOD_darkest_purple;
	HASH_ADD_STR(colors, name, c);
	
	// desaturated_fuchsia
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "desaturated_fuchsia");
	c->color = TCOD_desaturated_fuchsia;
	HASH_ADD_STR(colors, name, c);
	
	// lightest_fuchsia
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lightest_fuchsia");
	c->color = TCOD_lightest_fuchsia;
	HASH_ADD_STR(colors, name, c);
	
	// lighter_fuchsia
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lighter_fuchsia");
	c->color = TCOD_lighter_fuchsia;
	HASH_ADD_STR(colors, name, c);
	
	// light_fuchsia
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "light_fuchsia");
	c->color = TCOD_light_fuchsia;
	HASH_ADD_STR(colors, name, c);
	
	// dark_fuchsia
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "dark_fuchsia");
	c->color = TCOD_dark_fuchsia;
	HASH_ADD_STR(colors, name, c);
	
	// darker_fuchsia
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darker_fuchsia");
	c->color = TCOD_darker_fuchsia;
	HASH_ADD_STR(colors, name, c);
	
	// darkest_fuchsia
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darkest_fuchsia");
	c->color = TCOD_darkest_fuchsia;
	HASH_ADD_STR(colors, name, c);
	
	// desaturated_magenta
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "desaturated_magenta");
	c->color = TCOD_desaturated_magenta;
	HASH_ADD_STR(colors, name, c);
	
	// lightest_magenta
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lightest_magenta");
	c->color = TCOD_lightest_magenta;
	HASH_ADD_STR(colors, name, c);
	
	// lighter_magenta
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lighter_magenta");
	c->color = TCOD_lighter_magenta;
	HASH_ADD_STR(colors, name, c);
	
	// light_magenta
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "light_magenta");
	c->color = TCOD_light_magenta;
	HASH_ADD_STR(colors, name, c);
	
	// dark_magenta
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "dark_magenta");
	c->color = TCOD_dark_magenta;
	HASH_ADD_STR(colors, name, c);
	
	// darker_magenta
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darker_magenta");
	c->color = TCOD_darker_magenta;
	HASH_ADD_STR(colors, name, c);
	
	// darkest_magenta
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darkest_magenta");
	c->color = TCOD_darkest_magenta;
	HASH_ADD_STR(colors, name, c);
	
	// desaturated_pink
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "desaturated_pink");
	c->color = TCOD_desaturated_pink;
	HASH_ADD_STR(colors, name, c);
	
	// lightest_pink
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lightest_pink");
	c->color = TCOD_lightest_pink;
	HASH_ADD_STR(colors, name, c);
	
	// lighter_pink
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lighter_pink");
	c->color = TCOD_lighter_pink;
	HASH_ADD_STR(colors, name, c);
	
	// light_pink
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "light_pink");
	c->color = TCOD_light_pink;
	HASH_ADD_STR(colors, name, c);
	
	// dark_pink
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "dark_pink");
	c->color = TCOD_dark_pink;
	HASH_ADD_STR(colors, name, c);
	
	// darker_pink
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darker_pink");
	c->color = TCOD_darker_pink;
	HASH_ADD_STR(colors, name, c);
	
	// darkest_pink
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darkest_pink");
	c->color = TCOD_darkest_pink;
	HASH_ADD_STR(colors, name, c);
	
	// desaturated_crimson
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "desaturated_crimson");
	c->color = TCOD_desaturated_crimson;
	HASH_ADD_STR(colors, name, c);
	
	// lightest_crimson
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lightest_crimson");
	c->color = TCOD_lightest_crimson;
	HASH_ADD_STR(colors, name, c);
	
	// lighter_crimson
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lighter_crimson");
	c->color = TCOD_lighter_crimson;
	HASH_ADD_STR(colors, name, c);
	
	// light_crimson
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "light_crimson");
	c->color = TCOD_light_crimson;
	HASH_ADD_STR(colors, name, c);
	
	// dark_crimson
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "dark_crimson");
	c->color = TCOD_dark_crimson;
	HASH_ADD_STR(colors, name, c);
	
	// darker_crimson
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darker_crimson");
	c->color = TCOD_darker_crimson;
	HASH_ADD_STR(colors, name, c);
	
	// darkest_crimson
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darkest_crimson");
	c->color = TCOD_darkest_crimson;
	HASH_ADD_STR(colors, name, c);
	
	// lightest_gray
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lightest_gray");
	c->color = TCOD_lightest_gray;
	HASH_ADD_STR(colors, name, c);
	
	// lighter_gray
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lighter_gray");
	c->color = TCOD_lighter_gray;
	HASH_ADD_STR(colors, name, c);
	
	// light_gray
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "light_gray");
	c->color = TCOD_light_gray;
	HASH_ADD_STR(colors, name, c);
	
	// dark_gray
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "dark_gray");
	c->color = TCOD_dark_gray;
	HASH_ADD_STR(colors, name, c);
	
	// darker_gray
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darker_gray");
	c->color = TCOD_darker_gray;
	HASH_ADD_STR(colors, name, c);
	
	// darkest_gray
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darkest_gray");
	c->color = TCOD_darkest_gray;
	HASH_ADD_STR(colors, name, c);
	
	// lightest_sepia
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lightest_sepia");
	c->color = TCOD_lightest_sepia;
	HASH_ADD_STR(colors, name, c);
	
	// lighter_sepia
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "lighter_sepia");
	c->color = TCOD_lighter_sepia;
	HASH_ADD_STR(colors, name, c);
	
	// light_sepia
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "light_sepia");
	c->color = TCOD_light_sepia;
	HASH_ADD_STR(colors, name, c);
	
	// dark_sepia
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "dark_sepia");
	c->color = TCOD_dark_sepia;
	HASH_ADD_STR(colors, name, c);
	
	// darker_sepia
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darker_sepia");
	c->color = TCOD_darker_sepia;
	HASH_ADD_STR(colors, name, c);
	
	// darkest_sepia
	c = malloc(sizeof(COLOR));
	strcpy(c->name, "darkest_sepia");
	c->color = TCOD_darkest_sepia;
	HASH_ADD_STR(colors, name, c);
}
