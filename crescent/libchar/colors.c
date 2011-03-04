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
typedef struct { char name[30]; char c; UT_hash_handle hh; } CHAR;

CHAR *chars = NULL;

void init_chars()
{
	CHAR *c;
	
	// HLINE
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "hline");
	c->c = TCOD_CHAR_HLINE;
	HASH_ADD_STR(chars, name, c);
	
	// VLINE
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "vline");
	c->c = TCOD_CHAR_VLINE;
	HASH_ADD_STR(chars, name, c);
	
	// NE
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "ne");
	c->c = TCOD_CHAR_NE;
	HASH_ADD_STR(chars, name, c);
	
	// NW
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "nw");
	c->c = TCOD_CHAR_NW;
	HASH_ADD_STR(chars, name, c);
	
	// SE
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "se");
	c->c = TCOD_CHAR_SE;
	HASH_ADD_STR(chars, name, c);
	
	// SW
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "sw");
	c->c = TCOD_CHAR_SW;
	HASH_ADD_STR(chars, name, c);
	
	// DHLINE
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "dhline");
	c->c = TCOD_CHAR_DHLINE;
	HASH_ADD_STR(chars, name, c);
	
	// DVLINE
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "dvline");
	c->c = TCOD_CHAR_DVLINE;
	HASH_ADD_STR(chars, name, c);
	
	// DNE
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "dne");
	c->c = TCOD_CHAR_DNE;
	HASH_ADD_STR(chars, name, c);
	
	// DNW
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "dnw");
	c->c = TCOD_CHAR_DNW;
	HASH_ADD_STR(chars, name, c);
	
	// DSE
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "dse");
	c->c = TCOD_CHAR_DSE;
	HASH_ADD_STR(chars, name, c);
	
	// DSW
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "dsw");
	c->c = TCOD_CHAR_DSW;
	HASH_ADD_STR(chars, name, c);
	
	// TEEW
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "teew");
	c->c = TCOD_CHAR_TEEW;
	HASH_ADD_STR(chars, name, c);
	
	// TEEE
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "teee");
	c->c = TCOD_CHAR_TEEE;
	HASH_ADD_STR(chars, name, c);
	
	// TEEN
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "teen");
	c->c = TCOD_CHAR_TEEN;
	HASH_ADD_STR(chars, name, c);
	
	// TEES
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "tees");
	c->c = TCOD_CHAR_TEES;
	HASH_ADD_STR(chars, name, c);
	
	// DTEEW
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "dteew");
	c->c = TCOD_CHAR_DTEEW;
	HASH_ADD_STR(chars, name, c);
	
	// DTEEE
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "dteee");
	c->c = TCOD_CHAR_DTEEE;
	HASH_ADD_STR(chars, name, c);
	
	// DTEEN
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "dteen");
	c->c = TCOD_CHAR_DTEEN;
	HASH_ADD_STR(chars, name, c);
	
	// DTEES
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "dtees");
	c->c = TCOD_CHAR_DTEES;
	HASH_ADD_STR(chars, name, c);
	
	// BLOCK1
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "block1");
	c->c = TCOD_CHAR_BLOCK1;
	HASH_ADD_STR(chars, name, c);
	
	// BLOCK2
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "block2");
	c->c = TCOD_CHAR_BLOCK2;
	HASH_ADD_STR(chars, name, c);
	
	// BLOCK3
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "block3");
	c->c = TCOD_CHAR_BLOCK3;
	HASH_ADD_STR(chars, name, c);
	
	// CROSS
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "cross");
	c->c = TCOD_CHAR_CROSS;
	HASH_ADD_STR(chars, name, c);
	
	// ARROW_N
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "arrow_n");
	c->c = TCOD_CHAR_ARROW_N;
	HASH_ADD_STR(chars, name, c);
	
	// ARROW_S
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "arrow_s");
	c->c = TCOD_CHAR_ARROW_S;
	HASH_ADD_STR(chars, name, c);
	
	// ARROW_E
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "arrow_e");
	c->c = TCOD_CHAR_ARROW_E;
	HASH_ADD_STR(chars, name, c);
	
	// ARROW_W
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "arrow_w");
	c->c = TCOD_CHAR_ARROW_W;
	HASH_ADD_STR(chars, name, c);
	
	// ARROW2_N
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "arrow2_n");
	c->c = TCOD_CHAR_ARROW2_N;
	HASH_ADD_STR(chars, name, c);
	
	// ARROW2_S
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "arrow2_s");
	c->c = TCOD_CHAR_ARROW2_S;
	HASH_ADD_STR(chars, name, c);
	
	// ARROW2_E
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "arrow2_e");
	c->c = TCOD_CHAR_ARROW2_E;
	HASH_ADD_STR(chars, name, c);
	
	// ARROW2_W
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "arrow2_w");
	c->c = TCOD_CHAR_ARROW2_W;
	HASH_ADD_STR(chars, name, c);
	
	// DARROW_H
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "darrow_h");
	c->c = TCOD_CHAR_DARROW_H;
	HASH_ADD_STR(chars, name, c);
	
	// CHECKBOX_UNSET
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "checkbox_unset");
	c->c = TCOD_CHAR_CHECKBOX_UNSET;
	HASH_ADD_STR(chars, name, c);
	
	// CHECKBOX_SET
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "checkbox_set");
	c->c = TCOD_CHAR_CHECKBOX_SET;
	HASH_ADD_STR(chars, name, c);
	
	// RADIO_UNSET
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "radio_unset");
	c->c = TCOD_CHAR_RADIO_UNSET;
	HASH_ADD_STR(chars, name, c);
	
	// RADIO_SET
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "radio_set");
	c->c = TCOD_CHAR_RADIO_SET;
	HASH_ADD_STR(chars, name, c);
	
	// SUBP_NW
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "subp_nw");
	c->c = TCOD_CHAR_SUBP_NW;
	HASH_ADD_STR(chars, name, c);
	
	// SUBP_NE
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "subp_ne");
	c->c = TCOD_CHAR_SUBP_NE;
	HASH_ADD_STR(chars, name, c);
	
	// SUBP_N
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "subp_n");
	c->c = TCOD_CHAR_SUBP_N;
	HASH_ADD_STR(chars, name, c);
	
	// SUBP_SE
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "subp_se");
	c->c = TCOD_CHAR_SUBP_SE;
	HASH_ADD_STR(chars, name, c);
	
	// SUBP_DIAG
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "subp_diag");
	c->c = TCOD_CHAR_SUBP_DIAG;
	HASH_ADD_STR(chars, name, c);
	
	// SUBP_E
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "subp_e");
	c->c = TCOD_CHAR_SUBP_E;
	HASH_ADD_STR(chars, name, c);
	
	// SUBP_SW
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "subp_sw");
	c->c = TCOD_CHAR_SUBP_SW;
	HASH_ADD_STR(chars, name, c);
	
	// HEART
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "heart");
	c->c = TCOD_CHAR_HEART;
	HASH_ADD_STR(chars, name, c);
	
	// DIAMOND
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "diamond");
	c->c = TCOD_CHAR_DIAMOND;
	HASH_ADD_STR(chars, name, c);
	
	// CLUB
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "club");
	c->c = TCOD_CHAR_CLUB;
	HASH_ADD_STR(chars, name, c);
	
	// SPADE
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "spade");
	c->c = TCOD_CHAR_SPADE;
	HASH_ADD_STR(chars, name, c);
	
	// BULLET
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "bullet");
	c->c = TCOD_CHAR_BULLET;
	HASH_ADD_STR(chars, name, c);
	
	// BULLET_INV
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "bullet_inv");
	c->c = TCOD_CHAR_BULLET_INV;
	HASH_ADD_STR(chars, name, c);
	
	// MALE
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "male");
	c->c = TCOD_CHAR_MALE;
	HASH_ADD_STR(chars, name, c);
	
	// FEMALE
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "female");
	c->c = TCOD_CHAR_FEMALE;
	HASH_ADD_STR(chars, name, c);
	
	// NOTE
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "note");
	c->c = TCOD_CHAR_NOTE;
	HASH_ADD_STR(chars, name, c);
	
	// NOTE_DOUBLE
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "note_double");
	c->c = TCOD_CHAR_NOTE_DOUBLE;
	HASH_ADD_STR(chars, name, c);
	
	// LIGHT
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "light");
	c->c = TCOD_CHAR_LIGHT;
	HASH_ADD_STR(chars, name, c);
	
	// EXCLAM_DOUBLE
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "exclam_double");
	c->c = TCOD_CHAR_EXCLAM_DOUBLE;
	HASH_ADD_STR(chars, name, c);
	
	// PILCROW
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "pilcrow");
	c->c = TCOD_CHAR_PILCROW;
	HASH_ADD_STR(chars, name, c);
	
	// SECTION
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "section");
	c->c = TCOD_CHAR_SECTION;
	HASH_ADD_STR(chars, name, c);
	
	// POUND
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "pound");
	c->c = TCOD_CHAR_POUND;
	HASH_ADD_STR(chars, name, c);
	
	// MULTIPLICATION
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "multiplication");
	c->c = TCOD_CHAR_MULTIPLICATION;
	HASH_ADD_STR(chars, name, c);
	
	// FUNCTION
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "function");
	c->c = TCOD_CHAR_FUNCTION;
	HASH_ADD_STR(chars, name, c);
	
	// RESERVED
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "reserved");
	c->c = TCOD_CHAR_RESERVED;
	HASH_ADD_STR(chars, name, c);
	
	// HALF
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "half");
	c->c = TCOD_CHAR_HALF;
	HASH_ADD_STR(chars, name, c);
	
	// ONE_QUARTER
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "one_quarter");
	c->c = TCOD_CHAR_ONE_QUARTER;
	HASH_ADD_STR(chars, name, c);
	
	// COPYRIGHT
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "copyright");
	c->c = TCOD_CHAR_COPYRIGHT;
	HASH_ADD_STR(chars, name, c);
	
	// CENT
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "cent");
	c->c = TCOD_CHAR_CENT;
	HASH_ADD_STR(chars, name, c);
	
	// YEN
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "yen");
	c->c = TCOD_CHAR_YEN;
	HASH_ADD_STR(chars, name, c);
	
	// CURRENCY
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "currency");
	c->c = TCOD_CHAR_CURRENCY;
	HASH_ADD_STR(chars, name, c);
	
	// THREE_QUARTERS
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "three_quarters");
	c->c = TCOD_CHAR_THREE_QUARTERS;
	HASH_ADD_STR(chars, name, c);
	
	// DIVISION
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "division");
	c->c = TCOD_CHAR_DIVISION;
	HASH_ADD_STR(chars, name, c);
	
	// GRADE
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "grade");
	c->c = TCOD_CHAR_GRADE;
	HASH_ADD_STR(chars, name, c);
	
	// UMLAUT
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "umlaut");
	c->c = TCOD_CHAR_UMLAUT;
	HASH_ADD_STR(chars, name, c);
	
	// POW1
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "pow1");
	c->c = TCOD_CHAR_POW1;
	HASH_ADD_STR(chars, name, c);
	
	// POW3
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "pow3");
	c->c = TCOD_CHAR_POW3;
	HASH_ADD_STR(chars, name, c);
	
	// POW2
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "pow2");
	c->c = TCOD_CHAR_POW2;
	HASH_ADD_STR(chars, name, c);
	
	// BULLET_SQUARE
	c = malloc(sizeof(CHAR));
	strcpy(c->name, "bullet_square");
	c->c = TCOD_CHAR_BULLET_SQUARE;
	HASH_ADD_STR(chars, name, c);
}
char* key(TCOD_keycode_t vk)
{
		if(vk == TCODK_ESCAPE) return "escape";
		else if(vk == TCODK_BACKSPACE) return "backspace";
		else if(vk == TCODK_TAB) return "tab";
		else if(vk == TCODK_ENTER) return "enter";
		else if(vk == TCODK_SHIFT) return "shift";
		else if(vk == TCODK_CONTROL) return "control";
		else if(vk == TCODK_ALT) return "alt";
		else if(vk == TCODK_PAUSE) return "pause";
		else if(vk == TCODK_CAPSLOCK) return "capslock";
		else if(vk == TCODK_PAGEUP) return "pageup";
		else if(vk == TCODK_PAGEDOWN) return "pagedown";
		else if(vk == TCODK_END) return "end";
		else if(vk == TCODK_HOME) return "home";
		else if(vk == TCODK_UP) return "up";
		else if(vk == TCODK_LEFT) return "left";
		else if(vk == TCODK_RIGHT) return "right";
		else if(vk == TCODK_DOWN) return "down";
		else if(vk == TCODK_PRINTSCREEN) return "printscreen";
		else if(vk == TCODK_INSERT) return "insert";
		else if(vk == TCODK_DELETE) return "delete";
		else if(vk == TCODK_LWIN) return "lwin";
		else if(vk == TCODK_RWIN) return "rwin";
		else if(vk == TCODK_APPS) return "apps";
		else if(vk == TCODK_KPADD) return "kpadd";
		else if(vk == TCODK_KPSUB) return "kpsub";
		else if(vk == TCODK_KPDIV) return "kpdiv";
		else if(vk == TCODK_KPMUL) return "kpmul";
		else if(vk == TCODK_KPDEC) return "kpdec";
		else if(vk == TCODK_KPENTER) return "kpenter";
		else if(vk == TCODK_F1) return "f1";
		else if(vk == TCODK_F2) return "f2";
		else if(vk == TCODK_F3) return "f3";
		else if(vk == TCODK_F4) return "f4";
		else if(vk == TCODK_F5) return "f5";
		else if(vk == TCODK_F6) return "f6";
		else if(vk == TCODK_F7) return "f7";
		else if(vk == TCODK_F8) return "f8";
		else if(vk == TCODK_F9) return "f9";
		else if(vk == TCODK_F10) return "f10";
		else if(vk == TCODK_F11) return "f11";
		else if(vk == TCODK_F12) return "f12";
		else if(vk == TCODK_NUMLOCK) return "numlock";
		else if(vk == TCODK_SCROLLLOCK) return "scrolllock";
		else if(vk == TCODK_SPACE) return "space";
		else if(vk == TCODK_0) return "0";
		else if(vk == TCODK_1) return "1";
		else if(vk == TCODK_2) return "2";
		else if(vk == TCODK_3) return "3";
		else if(vk == TCODK_4) return "4";
		else if(vk == TCODK_5) return "5";
		else if(vk == TCODK_6) return "6";
		else if(vk == TCODK_7) return "7";
		else if(vk == TCODK_8) return "8";
		else if(vk == TCODK_9) return "9";
		else if(vk == TCODK_KP0) return "kp0";
		else if(vk == TCODK_KP1) return "kp1";
		else if(vk == TCODK_KP2) return "kp2";
		else if(vk == TCODK_KP3) return "kp3";
		else if(vk == TCODK_KP4) return "kp4";
		else if(vk == TCODK_KP5) return "kp5";
		else if(vk == TCODK_KP6) return "kp6";
		else if(vk == TCODK_KP7) return "kp7";
		else if(vk == TCODK_KP8) return "kp8";
		else if(vk == TCODK_KP9) return "kp9";
		else if(vk == TCODK_CHAR) return "char";
		else return "";
}
