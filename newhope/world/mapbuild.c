#include "mapbuild.h"

#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "util/pointhash.h"

static void map_polygons(Map *map);
static void map_coastline(Map *map);
static void map_elevation(Map *map);
static void map_rivers(Map *map);
static void map_moisture(Map *map);
static void map_biomes(Map *map);
static void map_noise(Map *map);
static void map_cities(Map *map);
static void map_roads(Map *map);

static PointHash* map_point_neighbours(Map* map);
static int distance_from_water(Map* map, Point p);
static void create_river(Map* map, PointList* plist, Point p);
static int neighbour_points(Map* map, Point p, Point** points);
static void free_plist(void *plist);


Map* map_init(MapParameters map_pars)
{
	Map* map = malloc(sizeof(Map));
	MapParameters* pars = malloc(sizeof(MapParameters));
	memcpy(pars, &map_pars, sizeof(MapParameters));
	map->parameters = pars;
	map->biomes = NULL;
	map->rivers = NULL;
	map->pt_altitudes = pointhash_init();

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
		}
		free(map->biomes);
	}
	for(i=0; i<map->n_rivers; i++)
		free(map->rivers[i].points);
	free(map->rivers);
	pointhash_free(map->pt_altitudes, NULL);
	pointhash_free(map->neighbours, &free_plist);
	free(map->parameters);
	free(map);
}


static void map_polygons(Map *map)
{
	debug("Generating map polygons...");

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
		map->biomes[i].avg_altitude = 0;
	}
	map->neighbours = map_point_neighbours(map);
	
	free(polygons);
}


static void map_coastline(Map *map)
{
	debug("Generating map coastline...");

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
	debug("Generating map elevation...");

	// set water elevation
	int i, j;
	for(i=0; i<map->n_biomes; i++)
	{
		Polygon* poly = map->biomes[i].polygon;
		if(map->biomes[i].terrain == t_WATER)
		{
			for(j=0; j<poly->n_segments; j++)
				pointhash_add(map->pt_altitudes, 
						poly->segments[j].p1, 
						(void*)-1, NULL);
			map->biomes[i].avg_altitude = -1;
		}
	}

	// set other tiles elevation
	for(i=0; i<map->n_biomes; i++)
	{
		Polygon* poly = map->biomes[i].polygon;
		if(map->biomes[i].terrain != t_WATER)
		{
			int tot_alt = 0;
			for(j=0; j<poly->n_segments; j++)
			{
				int alt = distance_from_water(
						map, poly->segments[j].p1);
				pointhash_add(map->pt_altitudes, 
						poly->segments[j].p1, 
						(void*)alt, NULL);
				tot_alt += alt;
			}
			map->biomes[i].avg_altitude = 
				tot_alt / poly->n_segments;
		}
	}
}


static void map_rivers(Map *map)
{
	debug("Generating rivers...");

	int rivers_left = map->parameters->n_rivers;
	map->rivers = calloc(sizeof(PointList), map->parameters->n_rivers);
	map->n_rivers = map->parameters->n_rivers;

	int i = 0;
	while(rivers_left > 0)
	{
		int b = rand() % map->n_biomes;
		if(map->biomes[b].terrain != t_WATER)
		{
			int seg = rand() % map->biomes[b].polygon->n_segments;
			Point p = map->biomes[b].polygon->segments[seg].p1;
			if(distance_from_water(map, p) > 400)
			{
				create_river(map, &map->rivers[i], p);
				--rivers_left;
				i++;
			}
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

/*
 * INTERNAL STATIC
 */

static PointHash* map_point_neighbours(Map* map)
{
	PointHash* ph = pointhash_init();
	for(int i=0; i<map->n_biomes; i++)
		for(int j=0; j<map->biomes[i].polygon->n_segments; j++)
		{
			Point p = map->biomes[i].polygon->segments[j].p1;
			PointList* list = calloc(sizeof(PointList), 1);
			list->n = neighbour_points(map, p, &list->points);
			pointhash_add(ph, p, list, free_plist);
		}

	return ph;
}


static int neighbour_points(Map* map, Point p, Point** points)
{
	int n = 0;

	for(int i=0; i<map->n_biomes; i++)
		for(int j=0; j<map->biomes[i].polygon->n_segments; j++)
		{
			Point p1 = map->biomes[i].polygon->segments[j].p1;
			Point p2 = map->biomes[i].polygon->segments[j].p2;

			Point new_point = { -1, -1 };
			if(p1.x == p.x && p1.y == p.y)
				new_point = p2;
			else if(p2.x == p.x && p2.y == p.y)
				new_point = p1;
			if(new_point.x != -1)
			{
				(*points) = realloc(
						(*points), sizeof(Point)*(n+1));
				(*points)[n++] = new_point;
			}
		}
	
	return n;
}


static int distance_from_water(Map* map, Point p)
{
	int dist = INT_MAX;
	for(int i=0; i<map->n_biomes; i++)
		if(map->biomes[i].terrain == t_WATER)
			for(int j=0; j<map->biomes[i].polygon->n_segments; j++)
			{
				Point ps = 
					map->biomes[i].polygon->segments[j].p1;
				int new_dist = distance(p, ps);
				if(new_dist < dist)
					dist = new_dist;
			}
	assert(dist != INT_MAX);
	return dist;
}


static void create_river(Map* map, PointList* river_plist, Point p)
{
	// find neighbours
	PointList* plist = pointhash_find(map->neighbours, p);

	// find lowest neighbour
	int cmp(const void* a, const void* b)
	{
		Point pa = *(Point*)a;
		Point pb = *(Point*)b;

		int alt_a = (int)pointhash_find(map->pt_altitudes, pa);
		int alt_b = (int)pointhash_find(map->pt_altitudes, pb);

		return alt_a - alt_b;
	}
	qsort(plist->points, plist->n, sizeof(Point), cmp);
	
	// add to point list
	(*river_plist).points = realloc(
			(*river_plist).points, 
			sizeof(Point) * ((*river_plist).n + 1));
	(*river_plist).points[(*river_plist).n] = plist->points[0];
	(*river_plist).n++;

	// find next segment
	if((int)pointhash_find(map->pt_altitudes, plist->points[0]) != -1)
		create_river(map, river_plist, plist->points[0]);
}


static void free_plist(void *plist) 
{ 
	PointList* pl = plist;
	free(pl->points); 
	free(pl);
}
