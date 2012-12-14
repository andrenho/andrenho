#ifndef TERRAINSURFACE_H
#define TERRAINSURFACE_H

#define TILESIZE 32

struct SDL_Surface;
struct SDL_Rect;

typedef struct TerrainSurface {
	struct SDL_Surface* sf;
} TerrainSurface;

TerrainSurface* trsurf_init();
void trsurf_free(TerrainSurface* ts);

void trsurf_resize(TerrainSurface* ts, int w, int h);
int trsurf_areas_to_redraw(TerrainSurface* ts, struct SDL_Rect** r, int* nrect);
void trsurf_set_topleft(TerrainSurface* ts, int x, int y);

#endif
