#ifndef TERRAINSURFACE_H
#define TERRAINSURFACE_H

#define TILESIZE 32

struct SDL_Surface;
struct World;
struct SDL_Rect;

typedef struct TerrainSurface {
	struct SDL_Surface* sf;
	struct World* world;
	int x, y, w, h;
} TerrainSurface;

TerrainSurface* trsurf_init(struct World* world);
void trsurf_free(TerrainSurface* ts);

void trsurf_resize(TerrainSurface* ts, int w, int h);
int trsurf_areas_to_redraw(TerrainSurface* ts, struct SDL_Rect** r, int* nrect);
void trsurf_set_topleft(TerrainSurface* ts, int x, int y);

#endif
