#include "dbggui.h"

#include "SDL_gfxPrimitives.h"

const int BLACK = 0x000000ff;
const int WHITE = 0xffffffff;

void 
DebugGUI::DrawStructure(Structure* structure)
{
	int x = structure->x * TILE;
	int y = structure->y * TILE;
	int w = structure->info->w * TILE;
	int h = structure->info->h * TILE;

	boxColor(screen, x, y, x+w, y+h, WHITE);
	rectangleColor(screen, x+1, y+1, x+w-1, y+h-1, BLACK);

	/*
	char* desc;
	if(structure->isResidence)
	{
		Residence* r = (Residence*)structure;
		if(r->
	*/
}
