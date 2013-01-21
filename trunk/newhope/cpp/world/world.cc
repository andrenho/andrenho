#include "world/world.h"

#include <algorithm>
#include <cstdlib>
#include <vector>

#include "util/logger.h"
#include "util/polygon.h"
#include "world/biome.h"
#include "world/city.h"

World::World(int w, int h) :
	w(w), h(h)
{
	logger.Debug("Building map...");
	MapParameters pars = {
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
}


World::~World()
{
	for(auto const& person: People)
		delete person;
	delete map;
	logger.Debug("World deleted.");
}


void
World::Process()
{
	for(auto& person: People) // TODO - only visible
		person->Process();
}


TerrainType 
World::Terrain(Point<int> p, bool ignore_paths) const
{
	// find rivers
	if(!ignore_paths)
	{
		if(std::binary_search(roadpts.begin(), roadpts.end(), p))
		{
			if(Terrain(p, true) != t_LAVAROCK)
				return t_LAVAROCK;
			else
				return t_DIRT;
		}
		if(std::binary_search(riverpts.begin(), riverpts.end(), p))
			return t_WATER;
		if(std::binary_search(lavapts.begin(), lavapts.end(), p))
			return t_LAVA;
	}

	// find biome
	unsigned int sz = map->biomes.size();
	for(unsigned int i=0; i<sz; i++)
		if(map->biomes[i]->polygon->PointInPolygon(p))
			return map->biomes[i]->terrain;
	return t_WATER;
}


int
World::Special(Point<int> p) const
{
	int n = rand() % 100;
	if(n >= 4)
		return 0;
	else
		return n;
}


void 
World::CreatePathsCache()
{
	logger.Debug("Drawing polygons...");

	static struct {
		std::vector<Polygon*> const& mapbuild;
		std::vector<IPoint>& points;
		int width;
	} polygons[] = {
		{ map->roads,  roadpts,  6 },
		{ map->rivers, riverpts, 5 },
		{ map->lava,   lavapts,  2 },
	};

	for(auto const& polygon: polygons)
	{
		// create a set with all the points
		std::set<IPoint> points;
		for(auto const& each: polygon.mapbuild)
			for(unsigned int i=0; i<each->points.size()-1; i++)
				AddPoints(each->points[i], each->points[i+1],
						points, polygon.width);

		// transform the set in a vector and sort it
		std::copy(points.begin(), points.end(), 
				std::back_inserter(polygon.points));
		std::sort(polygon.points.begin(), polygon.points.end());
		logger.Debug("%d", polygon.points.size());
	}
	
	logger.Debug("Polygons drawn.");
}


void
World::AddPoints(IPoint p1, IPoint p2, std::set<IPoint>& points, int line_width)
{
	int x0 = std::min(std::max(p1.x, 0), this->w - line_width),
	    y0 = std::min(std::max(p1.y, 0), this->h - line_width),
	    x1 = std::min(p2.x, this->w - line_width),
	    y1 = std::min(p2.y, this->h - line_width);
	int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
	int err = (dx>dy ? dx : -dy)/2, e2;

	for(;;)
	{
		int xx = 0; //rand() % w;
		int yy = 0; //rand() % w;
		for(int x=(-line_width/2); x<line_width/2; x++)
			for(int y=(-line_width/2); y<line_width/2; y++)
				points.insert(IPoint { x0+x+xx, y0+y+yy });
		if(x0 == x1 && y0 == y1)
			break;
		e2 = err;
		if(e2 > -dx)
		{
			err -= dy;
			x0 += sx;
		}
		if(e2 < dy)
		{
			err += dx;
			y0 += sy;
		}
	}
}
