#ifndef WORLD_WORLD_H
#define WORLD_WORLD_H

#include <set>
#include <vector>

#include "util/defines.h"
#include "util/point.h"
#include "util/mapcache.h"

class MapBuild;
class Person;

// the order is the importance
typedef enum {
	t_WATER		= 99,
	t_LAVA          = 98,
	t_SNOW          = 80,
	t_GRASS		= 50,
	t_LAVAROCK      = 5,
	t_DIRT          = 20,
	t_EARTH,
	t_ROCK,
	t_TUNDRA,
	t_HOTFOREST,
	t_COLDFOREST,

	t_RIVER,
	t_ROAD,

} TerrainType;

typedef enum { NO_TREE = 0, TREE_ROUND, TREE_POINTY } TreeType;

class World {
public:
	World(int w, int h);
	~World();

	void Process();
	TerrainType Terrain(Point<int> p, bool use_cache=true) const;
	int Special(Point<int> p) const;
	TreeType Tree(Point<int> p) const;

	static TerrainType TerrainCache(void* obj, Point<int> p);

	const int w, h;
	const MapBuild* map;
	std::vector<Person*> People;
	Person* Hero;

private:
	void CreatePathsCache();
	void AddPoints(Point<int> p1, Point<int> p2, 
			std::set<Point<int>>& points, int w);

	static TerrainType FindBiome(World* ths, Point<int> p);

	std::vector<Point<int>> riverpts, roadpts, lavapts;
	mapcache<Point<int>,TerrainType>* cache;
	int randspecial[100][100];

	DISALLOW_COPY_AND_ASSIGN(World);
};

#endif
