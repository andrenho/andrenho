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
		free_polygon(map->biomes[i].polygon);
	if(map->n_biomes > 0)
		free(map->biomes);
	free(map->parameters);
	free(map);
}


static void map_polygons(Map *map)
{
	int i;

	Polygon* polygons = NULL;
	int n = fake_voronoi(map->parameters->seed, 
			map->parameters->w, map->parameters->h, 30, &polygons);
	
	map->n_biomes = n;
	map->biomes = calloc(sizeof(Biome), n);
	for(i=0; i<n; i++)
	{
		map->biomes[i].polygon = &polygons[i];
		map->biomes[i].terrain = rand() % 2 ? t_DIRT : t_GRASS;
	}
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

