#include "mapbuild.h"

#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "util/log.h"
#include "util/pointhash.h"
#include "world/city.h"

static void map_polygons(Map *map);
static void map_coastline(Map *map);
static void map_elevation(Map *map);
static void map_rivers(Map *map);
static void map_moisture(Map *map);
static void map_lava(Map* map);
static void map_biomes(Map *map);
static void map_noise(Map *map);
static void map_cities(Map *map);
static void map_roads(Map *map);

static PointHash* map_point_neighbours(Map* map);
static int distance_from_water(Map* map, Point p, int including_rivers);
static void create_river(Map* map, PointList* plist, Point p);
static int neighbour_points(Map* map, Point p, Point** points);
static void free_plist(void *plist);
static int compare_lowest_neighbour(const void* a, const void* b, void* vmap);
static Point closest_neighbour(Point n, Point d);


Map* map_init(MapParameters map_pars)
{
	Map* map = malloc(sizeof(Map));
	MapParameters* pars = malloc(sizeof(MapParameters));
	memcpy(pars, &map_pars, sizeof(MapParameters));
	map->parameters = pars;
	map->biomes = NULL;
	map->rivers = NULL;
	map->roads = NULL;
	map->pt_altitudes = pointhash_init();

	map_polygons(map);
	map_coastline(map);
	map_elevation(map);
	map_rivers(map);
	map_moisture(map);
	map_lava(map);
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
	for(i=0; i<map->n_cities; i++)
		free_city(map->cities[i]);
	free(map->cities);
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
		map->biomes[i].terrain = t_DIRT;
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
	int n;
	for(i=0; i<6; i++)
	{
		while(map->biomes[(n = rand() % map->n_biomes)].terrain == t_WATER)
			;
		map->biomes[n].terrain = t_WATER;
	}
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
	int max_alt = 0;
	for(i=0; i<map->n_biomes; i++)
	{
		Polygon* poly = map->biomes[i].polygon;
		if(map->biomes[i].terrain != t_WATER)
		{
			int tot_alt = 0;
			for(j=0; j<poly->n_segments; j++)
			{
				int alt = distance_from_water(
						map, poly->segments[j].p1, 0);
				pointhash_add(map->pt_altitudes, 
						poly->segments[j].p1, 
						(void*)alt, NULL);
				if(alt > max_alt)
					max_alt = alt;
				tot_alt += alt;
			}
			map->biomes[i].avg_altitude = 
				tot_alt / poly->n_segments;
		}
	}

	// normalize elevation
	for(i=0; i<map->n_biomes; i++)
		if(map->biomes[i].avg_altitude != -1)
			map->biomes[i].avg_altitude =  
				(double)map->biomes[i].avg_altitude /
				(double)max_alt * 100;
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
			if(distance_from_water(map, p, 0) > 400)
			{
				create_river(map, &map->rivers[i], p);
				--rivers_left;
				i++;
			}
		}
	}
}


static void map_lava(Map* map)
{
	debug("Generating lava...");

	// find dryest, highest spot
	int min = INT_MAX;
	Point minpt = map->biomes[0].polygon->segments[0].p1;
	for(int i=0; i<map->n_biomes; i++)
	{
		if(map->biomes[i].terrain == t_WATER)
			continue;
		int avg = (100 - map->biomes[i].avg_altitude) + 
			map->biomes[i].moisture;
		if(min > avg)
		{
			min = avg;
			minpt = map->biomes[i].polygon->segments[0].p1;
		}
	}

	// draw lava path
	Point next = minpt;
	for(int i=0; i<LAVA_POINTS; i++)
	{
		Point* points = NULL;
		int n = neighbour_points(map, next, &points);
		qsort_r(points, n, sizeof(Point), compare_lowest_neighbour, map);
		int k = 0;
try_again:
		next = points[k];
		for(int j=0; j<i; j++)
			if(next.x == map->lava[j].x && next.y == map->lava[j].y)
			{
				++k;
				if(k >= n)
					break;
				goto try_again;
			}
		map->lava[i] = next;

		free(points);
	}
}


static void map_moisture(Map *map)
{
	debug("Generating map moisture...");

	// calculate moisture
	int max_moi = 0;
	for(int i=0; i<map->n_biomes; i++)
	{
		Polygon* poly = map->biomes[i].polygon;
		int tot_moi = 0;
		for(int j=0; j<poly->n_segments; j++)
		{
			int moi = distance_from_water(
					map, poly->segments[j].p1, 1);
			if(moi > max_moi)
				max_moi = moi;
			tot_moi += moi;
		}
		map->biomes[i].moisture = tot_moi / poly->n_segments;
	}

	// normalize and adjust moisture
	for(int i=0; i<map->n_biomes; i++)
		if(map->biomes[i].moisture != -1)
			map->biomes[i].moisture = 100 - ( 
				(double)map->biomes[i].moisture /
				(double)max_moi * 100);
}


static void map_biomes(Map *map)
{
	/*
	 * Elev/Moist   0-30       30-60      60-100
	 *  0-30        DIRT       EARTH      GRASS
	 * 30-60        ROCK       GRASS      HOTFOREST
	 * 60-100       LAVAROCK   SNOW       COLDFOREST
	 */
	for(int i=0; i<map->n_biomes; i++)
	{
		if(map->biomes[i].terrain == t_WATER)
			continue;

		int alt = map->biomes[i].avg_altitude;
		int moi = map->biomes[i].moisture;
		Terrain t = t_DIRT;
		if(alt < 10)
			t = t_DIRT;
		else if(alt < 35)
		{
			if(moi < 30)
				t = t_DIRT;
			else if(moi < 60)
				t = t_EARTH;
			else
				t = t_GRASS;
		}
		else if(alt < 70)
		{
			if(moi < 30)
				t = t_ROCK;
			else if(moi < 60)
				t = t_GRASS;
			else
				t = t_HOTFOREST;
		}
		else
		{
			if(moi < 30)
				t = t_LAVAROCK;
			else if(moi < 60)
				t = t_SNOW;
			else
				t = t_COLDFOREST;
		}
		map->biomes[i].terrain = t;
	}
}


static void map_noise(Map *map)
{
}


static void map_cities(Map *map)
{
	map->n_cities = map->parameters->n_cities;
	map->cities = calloc(sizeof(City*), map->parameters->n_cities);

	for(int i=0; i<map->parameters->n_cities; i++)
	{
		int b;
		do 
		{
			b = rand() % map->n_biomes; 
		} while(map->biomes[b].terrain == t_WATER);
		Point pos = map->biomes[b].polygon->midpoint;
		City* city = city_init(NULL, pos.x, pos.y);
		map->cities[i] = city;
	}
}


static void map_roads(Map *map)
{
	debug("Generating roads...");

	int roads_left = map->parameters->n_roads;
	map->roads = calloc(sizeof(PointList), map->parameters->n_roads);
	map->n_roads = map->parameters->n_roads;

	int i = 0;
	while(roads_left > 0)
	{
		// choose cities
		int b, c = rand() % map->n_cities;
try_again:
		b = rand() % map->n_cities;
		if(b == c)
			goto try_again;

		Point pstart = { map->cities[b]->x, map->cities[b]->y };
		Point pend   = { map->cities[c]->x, map->cities[c]->y };

		// first point of the road
		PointList* road = &map->roads[i];
		road->n = 1;
		road->points = calloc(sizeof(Point), 1);
		road->points[0] = pstart;

		while(pstart.x != pend.x && pstart.y != pend.y)
		{
			pstart = closest_neighbour(pstart, pend);
			road->points = realloc(sizeof(Point), road->n+1);
			road->points[road->n] = pstart;
			road->n++;
		}

		--roads_left;
		i++;
	}
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


static int distance_from_water(Map* map, Point p, int including_rivers)
{
	int dist = INT_MAX;

	// distance from sea
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

	// distance from river
	if(including_rivers)
		for(int i=0; i<map->n_rivers; i++)
			for(int j=0; j<map->rivers[i].n; j++)
			{
				Point ps = map->rivers[i].points[j];
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
	qsort_r(plist->points, plist->n, sizeof(Point), 
			compare_lowest_neighbour, map);

	// can't repeat point (avoid loops)
	int n = 0;
next_point:
	for(int i=0; i<(*river_plist).n; i++)
	{
		Point p1 = (*river_plist).points[i];
		Point p2 = plist->points[n];
		if(p1.x == p2.x && p1.y == p2.y)
		{
			++n;
			if(n == plist->n)
				return;
			goto next_point;
		}
	}

	
	// add to point list
	(*river_plist).points = realloc(
			(*river_plist).points, 
			sizeof(Point) * ((*river_plist).n + 1));
	(*river_plist).points[(*river_plist).n] = plist->points[n];
	(*river_plist).n++;

	// find next segment
	if((int)pointhash_find(map->pt_altitudes, plist->points[n]) != -1)
		create_river(map, river_plist, plist->points[n]);
}


static void free_plist(void *plist) 
{ 
	PointList* pl = plist;
	free(pl->points); 
	free(pl);
}


static int compare_lowest_neighbour(const void* a, const void* b, void* vmap)
{
	Map* map = vmap;
	Point pa = *(Point*)a;
	Point pb = *(Point*)b;

	int alt_a = (int)pointhash_find(map->pt_altitudes, pa);
	int alt_b = (int)pointhash_find(map->pt_altitudes, pb);

	return alt_a - alt_b;
}


// returns the neighbour of 'n' closest to 'd'
static Point closest_neighbour(Point n, Point d)
{
	
}
