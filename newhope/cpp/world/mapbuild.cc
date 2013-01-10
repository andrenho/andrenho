#include "world/mapbuild.h"

#include <vector>

#include "util/logger.h"
#include "util/polygon.h"
#include "world/biome.h"

MapBuild::MapBuild(struct MapParameters const& pars)
	: pars(pars)
{
	CreatePolygons();
	CreateCoastline();
}


MapBuild::~MapBuild()
{
}


void
MapBuild::CreatePolygons()
{
	logger.Debug("Generating map polygons...");

	// create layout
	std::vector<Polygon*> polygons;
	Polygon::FakeVoronoi(pars.seed, pars.w, pars.h, 30, polygons);

	// add biomes
	for(std::vector<Polygon*>::iterator it = polygons.begin(); 
			it != polygons.end(); it++)
		biomes.push_back(new Biome(*it));
}


void
MapBuild::CreateCoastline()
{
	logger.Debug("Generating map coastline...");

	// middle square
	int qw = pars.w / 6,
	    qh = pars.h / 6;
	struct Point pts[] = { { qw, qh }, { qw*5, qh }, 
		{ qw*5, qh*5 }, { qw, qh*5 } };

	// disturb points
	int max_disturb = qw;
	for(int i=0; i<4; i++)
	{
		pts[i].x += (rand() % max_disturb) - max_disturb/2;
		pts[i].y += (rand() % max_disturb) - max_disturb/2;
	}
	
	// create coastline
	Polygon polygon(pts, 4);
	polygon.MidlineDisplacement(3);
	for(std::vector<Biome*>::const_iterator biome = biomes.begin();
			biome != biomes.end(); biome++)
	{
		Point p = (*biome)->polygon->Midpoint();
		if(!polygon.ContainsPoint(p))
			(*biome)->terrain = t_WATER;
	}
}


void
MapBuild::CreateLakes()
{
	// add lakes
	logger.Debug("Adding lakes...");
	for(int i=0; i<rand()%2+3; i++)
	{
		Rect r(rand() % 3000 + 800, rand() % 3000 + 800,
				rand() % 500 + 100, rand() % 500 + 100);
		Polygon lake(r);
		lake.Debug();
		lake.MidlineDisplacement(2);
		for(std::vector<Biome*>::const_iterator biome = biomes.begin();
				biome != biomes.end(); biome++)
		{
			Point p = (*biome)->polygon->Midpoint();
			if(lake.ContainsPoint(p))
				(*biome)->terrain = t_WATER;
		}
	}
}
