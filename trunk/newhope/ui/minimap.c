#include "minimap.h"

#include <stdlib.h>
#include "SDL.h"


Minimap* minimap_init(struct World* world)
{
	Minimap* mm = malloc(sizeof(Minimap));
	mm->sf = NULL;
	minimap_reset(mm);
	return mm;
}


void minimap_free(Minimap* mm)
{
	if(mm->sf)
		SDL_FreeSurface(mm->sf);
	free(mm);
}


void minimap_reset(Minimap* mm)
{
}


void minimap_display(Minimap* mm, struct UI* ui)
{
}
