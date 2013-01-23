#include "world/world.h"

#include <algorithm>
#include <cstdlib>
#include <vector>
using namespace std;

#include "util/logger.h"
#include "util/mapcache.h"
#include "util/polygon.h"
#include "world/biome.h"
#include "world/city.h"
#include "world/mapbuild.h"
#include "world/person.h"

World::World(int w, int h) :
	w(w), h(h)
{
	logger.Debug("Building map...");
	MapParameters pars {
		.seed = 2,
		.w = w,
		.h = h,
		.n_rivers = 15,
		.n_cities = 20,
		.n_roads = 10,
	};
	map = new MapBuild(pars);
	logger.Debug("Map built.");

	// create vectors with rivers, lava and roads
	CreatePathsCache();

	// add people
	People.push_back(new Person(*this, map->cities[0]->pos));
	Hero = People[0];

	// create terrain cache
	cache = new mapcache<Point<int>,TerrainType>(4000, TerrainCache, this);

	// randomize terrain
	for(int i(0); i<100; i++) {
		for(int j(0); j<100; j++) {
			randspecial[i][j] = rand() % 100;
		}
	}
}


World::~World()
{
	delete cache;
	for(const auto& person: People) {
		delete person;
	}
	delete map;
	logger.Debug("World deleted.");
}


void
World::Process()
{
	for(auto& person: People) { // TODO - only visible
		person->Process();
	}
}


TerrainType 
World::Terrain(Point<int> p, bool use_cache) const
{
	if(use_cache) {
		return (*cache)[p];
	} else {
		return TerrainCache((void*)this, p);
	}
}


TerrainType
World::FindBiome(World* ths, Point<int> p)
{
	// find biome
	unsigned int sz(ths->map->biomes.size());
	for(unsigned int i(0); i<sz; i++) {
		if(ths->map->biomes[i]->polygon->PointInPolygon(p)) {
			return ths->map->biomes[i]->terrain;
		}
	}
	return t_WATER;
}


TerrainType 
World::TerrainCache(void* obj, Point<int> p)
{
	World* ths((World*)obj);

	if(binary_search(ths->roadpts.begin(), ths->roadpts.end(), p))
	{
		if(FindBiome(ths, p) != t_LAVAROCK)
			return t_ROAD;
		else
			return t_DIRT;
	}
	if(binary_search(ths->riverpts.begin(), ths->riverpts.end(), p)) {
		return t_RIVER;
	}
	if(binary_search(ths->lavapts.begin(), ths->lavapts.end(), p)) {
		return t_LAVA;
	}

	return FindBiome(ths, p);
}


int
World::Special(Point<int> p) const
{
	return randspecial[p.x % 100][p.y % 100];
}


TreeType 
World::Tree(Point<int> p) const
{
	const int DENSITY_NO_FOREST = 99,
	          DENSITY_FOREST = 20;
	TerrainType tr = Terrain(p);
	if(tr == t_SNOW || tr == t_TUNDRA) {
		if(Special(p) >= DENSITY_NO_FOREST) {
			return TREE_POINTY;
		}
	} else if(tr == t_COLDFOREST) {
		if(Special(p) >= DENSITY_FOREST) {
			return TREE_POINTY;
		}
	} else if(tr == t_GRASS) {
		if(Special(p) >= DENSITY_NO_FOREST) {
			return TREE_ROUND;
		}
	} else if(tr == t_HOTFOREST) {
		if(Special(p) >= DENSITY_FOREST) {
			return TREE_ROUND;
		}
	}
	return NO_TREE; // TODO - add desert trees
}


void 
World::CreatePathsCache()
{
	logger.Debug("Drawing polygons...");

	static struct {
		vector<Polygon*> const& mapbuild;
		vector<Point<int>>& points;
		int width;
	} polygons[] {
		{ map->roads,  roadpts,  6 },
		{ map->rivers, riverpts, 5 },
		{ map->lava,   lavapts,  2 },
	};

	for(const auto& polygon: polygons) {
		// create a set with all the points
		set<Point<int>> points;
		for(const auto& each: polygon.mapbuild) {
			for(unsigned int i=0; i<each->points.size()-1; i++) {
				AddPoints(each->points[i], each->points[i+1],
						points, polygon.width);
			}
		}

		// transform the set in a vector and sort it
		copy(points.begin(), points.end(), back_inserter(polygon.points));
		sort(polygon.points.begin(), polygon.points.end());
		logger.Debug("%d", polygon.points.size());
	}
	
	logger.Debug("Polygons drawn.");
}


void
World::AddPoints(Point<int> p1, Point<int> p2, set<Point<int>>& points, 
		int line_width)
{
	int x0(min(max(p1.x, 0), this->w - line_width)),
	    y0(min(max(p1.y, 0), this->h - line_width)),
	    x1(min(p2.x, this->w - line_width)),
	    y1(min(p2.y, this->h - line_width));
	int dx(abs(x1-x0)), sx(x0<x1 ? 1 : -1);
	int dy(abs(y1-y0)), sy(y0<y1 ? 1 : -1);
	int err((dx>dy ? dx : -dy)/2), e2;

	for(;;) {
		int xx(0);
		int yy(0);
		for(int x(-line_width/2); x<line_width/2; x++) {
			for(int y(-line_width/2); y<line_width/2; y++) {
				points.insert(Point<int>(x0+x+xx, y0+y+yy));
			}
		}
		if(x0 == x1 && y0 == y1) {
			break;
		}
		e2 = err;
		if(e2 > -dx) {
			err -= dy;
			x0 += sx;
		}
		if(e2 < dy) {
			err += dx;
			y0 += sy;
		}
	}
}
