#ifndef MAPBUILD_H
#define MAPBUILD_H

typedef struct MapParameters {
	int w, h;
} MapParameters;

typedef struct Map {
	MapParameters* parameters;
} Map;

Map* map_init(MapParameters map_pars);
void map_free(Map* map);

#endif
