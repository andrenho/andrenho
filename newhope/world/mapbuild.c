#include "mapbuild.h"

#include <stdlib.h>
#include <string.h>


static void map_polygons(Map *map);
static void map_coastline(Map *map);
static void map_elevation(Map *map);
static void map_rivers(Map *map);
static void map_moisture(Map *map);
static void map_biomes(Map *map);
static void map_noise(Map *map);
static void map_cities(Map *map);
static void map_roads(Map *map);


Map* map_init(MapParameters map_pars)
{
	Map* map = malloc(sizeof(Map));
	MapParameters* pars = malloc(sizeof(MapParameters));
	memcpy(pars, &map_pars, sizeof(MapParameters));
	map->parameters = pars;
	map->biomes = NULL;

	map_polygons(map);
	map_coastline(map);
	map_elevation(map);
	map_rivers(map);
	map_moisture(map);
	map_biomes(map);
	map_noise(map);
	map_cities(map);
	map_roads(map);

	return map;
}


void map_free(Map* map)
{
	int i;
	for(i=0; i<map->n_biomes; i++)
		free(map->biomes[i].polypt);
	if(map->n_biomes > 0)
		free(map->biomes);
	free(map->parameters);
	free(map);
}


static void map_polygons(Map *map)
{
	map->n_biomes = 1;
	map->biomes = calloc(sizeof(Biome), map->n_biomes);
	map->biomes[0].n_points = 3;
	map->biomes[0].polypt = calloc(sizeof(Point), map->biomes[0].n_points);
	map->biomes[0].polypt[0] = (Point){ 3, 3 };
	map->biomes[0].polypt[1] = (Point){ 20, 8 };
	map->biomes[0].polypt[2] = (Point){ 3, 12 };
	map->biomes[0].terrain = t_GRASS;
}


static void map_coastline(Map *map)
{
}


static void map_elevation(Map *map)
{
}


static void map_rivers(Map *map)
{
}


static void map_moisture(Map *map)
{
}


static void map_biomes(Map *map)
{
}


static void map_noise(Map *map)
{
}


static void map_cities(Map *map)
{
}


static void map_roads(Map *map)
{
}

