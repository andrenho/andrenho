#ifndef WORLD_WORLD_H
#define WORLD_WORLD_H

#include <set>
#include <vector>

#include "util/point.h"
#include "world/mapbuild.h"
#include "world/person.h"

// the order is the importance
typedef enum {
	t_INVALID       = -1,
	t_OUT_OF_BOUNDS	= 0,
	t_NOTHING       = 1,
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

class World {
public:
	World(int w, int h);
	~World();

	void Process();
	TerrainType Terrain(Point<int> p, bool ignore_paths=false) const;
	int Special(Point<int> p) const;

	const int w, h;
	const MapBuild* map;
	std::vector<Person*> People;
	Person* Hero;

private:
	void CreatePathsCache();
	void AddPoints(IPoint p1, IPoint p2, std::set<IPoint>& points, int w);

	std::vector<IPoint> riverpts, roadpts, lavapts;
};

#endif
