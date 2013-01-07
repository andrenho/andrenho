#include "mapbuild.h"

#include <assert.h>
#include <limits.h>
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

static int distance_from_water(Map* map, Point p);


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
	if(map->n_biomes > 0)
	{
		for(i=0; i<map->n_biomes; i++)
		{
			if(map->biomes[i].polygon)
				free_polygon(map->biomes[i].polygon);
			if(map->biomes[i].pt_altitudes)
				free(map->biomes[i].pt_altitudes);
		}
		free(map->biomes);
	}
	free(map->parameters);
	free(map);
}


static void map_polygons(Map *map)
{
	int i;

	Polygon** polygons = NULL;
	int n = fake_voronoi(map->parameters->seed, 
			map->parameters->w, map->parameters->h, 30, &polygons);
	
	map->n_biomes = n;
	map->biomes = calloc(sizeof(Biome), n);
	for(i=0; i<n; i++)
	{
		map->biomes[i].polygon = polygons[i];
		map->biomes[i].terrain = rand() % 2 ? t_DIRT : t_GRASS;
		map->biomes[i].pt_altitudes = NULL;
		map->biomes[i].avg_altitude = 0;
	}
	
	free(polygons);
}


static void map_coastline(Map *map)
{
	int i;

	// middle square
	int qw = map->parameters->w / 6,
	    qh = map->parameters->h / 6;
	Point pts[] = { { qw, qh }, { qw*5, qh }, { qw*5, qh*5 }, { qw, qh*5 } };

	// disturb points
	int max_disturb = qw;
	for(i=0; i<4; i++)
	{
		pts[i].x += (rand() % max_disturb) - max_disturb/2;
		pts[i].y += (rand() % max_disturb) - max_disturb/2;
	}
	
	// create coastline
	Polygon* polygon = create_polygon(4, pts);
	polygon = midline_displacement(polygon, 3);
	for(i=0; i<map->n_biomes; i++)
	{
		Point p = map->biomes[i].polygon->midpoint;
		if(!point_in_polygon(p, polygon))
			map->biomes[i].terrain = t_WATER;
	}
	free_polygon(polygon);

	// add lakes
	/*
	int n;
	for(i=0; i<6; i++)
	{
		while(map->biomes[(n = rand() % map->n_biomes)].terrain == t_WATER)
			;
		map->biomes[rand() % map->n_biomes].terrain = t_WATER;
	}
	*/
}


static void map_elevation(Map *map)
{
	// set water elevation
	int i, j;
	for(i=0; i<map->n_biomes; i++)
	{
		Polygon* poly = map->biomes[i].polygon;
		if(map->biomes[i].terrain == t_WATER)
		{
			map->biomes[i].pt_altitudes = 
				calloc(sizeof(int), poly->n_segments);
			for(j=0; j<poly->n_segments; j++)
				map->biomes[i].pt_altitudes[j] = -1;
			map->biomes[i].avg_altitude = -1;
		}
	}

	// set other tiles elevation
	for(i=0; i<map->n_biomes; i++)
	{
		Polygon* poly = map->biomes[i].polygon;
		if(map->biomes[i].terrain != t_WATER)
		{
			map->biomes[i].pt_altitudes = 
				calloc(sizeof(int), poly->n_segments);
			int tot_alt = 0;
			for(j=0; j<poly->n_segments; j++)
			{
				int alt = distance_from_water(
						map, poly->segments[j].p1);
				tot_alt += alt;
				map->biomes[i].pt_altitudes[j] = alt;
			}
			map->biomes[i].avg_altitude = 
				tot_alt / poly->n_segments;
		}
	}
}


static void map_rivers(Map *map)
{
	int rivers_left = map->parameters->n_rivers;
	while(rivers_left > 0)
	{
		int b = rand() % map->n_biomes;
		if(map->biomes[b].terrain != t_WATER)
		{
	//		int seg = map->biomes[
	//		int p = map->biomes[b].segments[

			free(conn_pts);
			--rivers_left;
		}
	}
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


static int distance_from_water(Map* map, Point p)
{
	int dist = INT_MAX;
	for(int i=0; i<map->n_biomes; i++)
		if(map->biomes[i].terrain == t_WATER)
			for(int j=0; j<map->biomes[j].polygon->n_segments; j++)
			{
				Point ps = 
					map->biomes[j].polygon->segments[j].p1;
				int new_dist = distance(p, ps);
				if(new_dist < dist)
					dist = new_dist;
			}
	assert(dist != INT_MAX);
	return dist;
}
