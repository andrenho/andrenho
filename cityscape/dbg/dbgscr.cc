#include "dbggui.h"

#include <algorithm>
#include <vector>
#include "SDL_gfxPrimitives.h"

#define DBG_BOX 150

const int BLACK = 0x000000ff;
const int WHITE = 0xffffffff;

void
DebugGUI::UpdateScreen()
{
	int nl = -8;

	// draw points
	/*
	for(int x=0; x<std::min(screen->w, city->w*TILE); x+=TILE)
		for(int y=0; y<std::min(screen->h, city->h*TILE); y+=TILE)
			pixelColor(screen, x+TILE-1, y+TILE-1, BLACK);
	*/

	// draw structures
	std::vector<Structure*>::iterator it;
	for(it=city->structures.begin(); it<city->structures.end(); it++)
		DrawStructure(*it);

	// debug box
	boxColor(screen, screen->w-DBG_BOX, 0, screen->w, screen->h, WHITE);
	vlineColor(screen, screen->w-DBG_BOX, 0, screen->h, BLACK);

	// debug info
	int dx = screen->w-DBG_BOX + 5;
	char s[256];
	Tile* t = getHoverTile();
	if(t)
	{
		sprintf(s, "%dx%d", t->x, t->y);
		stringColor(screen, dx, nl+=12, s, BLACK);
		if(t->ground == Tile::LAND)
			stringColor(screen, dx, nl+=12, "Land", BLACK);
		else
			stringColor(screen, dx, nl+=12, "Water", BLACK);

		nl+=12;

		if(!t->structure && t->ground == Tile::LAND)
			stringColor(screen, dx, nl+=12, "Bare land", BLACK);
	}

	// update screen
	SDL_Flip(screen);
}
