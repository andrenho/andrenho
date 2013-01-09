#include "world/mapbuild.h"

#include <vector>

#include "util/logger.h"
#include "util/polygon.h"
#include "world/biome.h"

MapBuild::MapBuild(struct MapParameters const& pars)
	: pars(pars)
{
	CreatePolygons();
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
