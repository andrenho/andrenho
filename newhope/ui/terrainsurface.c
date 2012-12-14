#include "terrainsurface.h"

#include "SDL.h"


TerrainSurface* trsurf_init()
{
	TerrainSurface* ts = malloc(sizeof(TerrainSurface));
	ts->sf = NULL;

	return ts;
}


void trsurf_free(TerrainSurface* ts)
{
	if(ts->sf)
		SDL_FreeSurface(ts->sf);
	free(ts);
}


void trsurf_resize(TerrainSurface* ts, int w, int h)
{
}


int trsurf_areas_to_redraw(TerrainSurface* ts, struct SDL_Rect** r, int* nrect)
{
	return 1;
}


void trsurf_set_topleft(TerrainSurface* ts, int x, int y)
{
}
