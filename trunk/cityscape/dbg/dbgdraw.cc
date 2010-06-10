#include "dbggui.h"

#include <string.h>

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

	char* desc;
	if(structure->isResidence())
	{
		Residence* r = (Residence*)structure;
		if(r->info->density == ResidentialInfo::LOW_D)
			switch(r->info->level)
			{
				case ResidentialInfo::LOW:
					desc = "lr"; break;					
				default:
					abort();
			}
		else
			switch(r->info->level)
			{
				case ResidentialInfo::LOW:
					desc = "LR"; break;					
				default:
					abort();
			}
	}
	else
		abort();

	x += w/2 - (strlen(desc) * 8 / 2);
	y += h/2 - 4;

	stringColor(screen, x, y, desc, BLACK);
}


void
DebugGUI::DrawPerson(Person* person)
{
	int x = (int)(person->x * TILE);
	int y = (int)(person->y * TILE);

	// aacircleColor(screen, (Sint16)x, (Sint16)y, 3, BLACK);
	aatrigonColor(screen, x, y-3, x-3, y+3, x+3, y+3, BLACK);
}
