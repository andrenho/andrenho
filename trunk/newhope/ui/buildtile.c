#include "ui/buildtile.h"

#include "SDL.h"

#include "ui/ui.h"
#include "ui/resource.h"
#include "util/log.h"
#include "world/world.h"

static struct {
	Terrain terrain;
	char* image;
} basic[] = {
	{ t_GRASS, "grass" },
	{ t_WATER, "water" },
	{ -1, NULL }
};


void build_tile(UI* ui, int x, int y, SDL_Surface* stack[MAX_STACK])
{
	int st = 0;
	int special = 0;
	Terrain terrain = world_terrain(ui->world, x, y, &special);
	
	int i = 0;
	while(basic[i].image)
	{
		if(terrain == basic[i].terrain)
		{
			if(!special)
				stack[st] = res(basic[i].image);
			else
			{
				char img[30];
				snprintf(img, 30, "%s_%d", basic[i].image,
						special);
				stack[st] = res(img);
			}
			++st;
			goto found;
		}
		++i;
	}
	
	if(terrain != t_OUT_OF_BOUNDS) // TODO
		errx(1, "Invalid terrain type.");
found:
	return;
}
