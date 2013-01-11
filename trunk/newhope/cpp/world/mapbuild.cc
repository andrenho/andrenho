#include "world/mapbuild.h"

#include <cassert>
#include <algorithm>
#include <vector>

#include "util/logger.h"
#include "util/polygon.h"
#include "world/biome.h"

MapBuild::MapBuild(struct MapParameters const& pars)
	: pars(pars)
{
	CreatePolygons();
	CreateCoastline();
	CreateLakes();
	CreateElevation();
	CreateRivers();
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
	int qw = pars.w / 8,
	    qh = pars.h / 8;
	struct Point pts[] = { { qw*2, qh*2 }, { qw*6, qh*2 }, 
		{ qw*6, qh*6 }, { qw*2, qh*6 } };

	// disturb points
	int max_disturb = qw;
	for(int i=0; i<4; i++)
	{
		pts[i].x += (rand() % max_disturb) - max_disturb/2;
		pts[i].y += (rand() % max_disturb) - max_disturb/2;
	}
	
	// create coastline
	Polygon polygon(pts, 4);
	polygon.Debug();
	logger.Debug("-------");
	polygon.MidlineDisplacement(1);
	polygon.Debug();
	for(std::vector<Biome*>::const_iterator biome = biomes.begin();
			biome != biomes.end(); biome++)
	{
		Point p = (*biome)->polygon->Midpoint();
		if(!polygon.PointInPolygon(p))
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
		lake.MidlineDisplacement(2);
		for(std::vector<Biome*>::const_iterator biome = biomes.begin();
				biome != biomes.end(); biome++)
		{
			Point p = (*biome)->polygon->Midpoint();
			if(lake.PointInPolygon(p))
				(*biome)->terrain = t_WATER;
		}
	}
}


void
MapBuild::CreateElevation()
{
	logger.Debug("Generating map elevation...");

	// set water elevation
	for(std::vector<Biome*>::const_iterator biome = biomes.begin();
			biome != biomes.end(); biome++)
		if((*biome)->terrain == t_WATER)
		{
			std::vector<Point>::const_iterator point;
			for(point = (*biome)->polygon->points.begin(); 
					point != (*biome)->polygon->points.end(); 
					point++)
				(*point).elevation = -1;
			(*biome)->elevation = -1;
		}

	// set other tiles elevation
	int max_alt;
	for(std::vector<Biome*>::const_iterator biome = biomes.begin();
			biome != biomes.end(); biome++)
		if((*biome)->terrain != t_WATER)
		{
			int tot_alt = 0;
			std::vector<Point>::const_iterator point;
			for(point = (*biome)->polygon->points.begin(); 
				point != (*biome)->polygon->points.end(); 
				point++)
			{
				(*point).elevation = DistanceFromWater(
						(*point), false);
				max_alt = std::max(tot_alt, (*point).elevation);
				tot_alt += (*point).elevation;
			}
			(*biome)->elevation = tot_alt / 
				(*biome)->polygon->points.size();
		}
	
	// normalize elevation
	for(std::vector<Biome*>::const_iterator biome = biomes.begin();
			biome != biomes.end(); biome++)
	{
		if((*biome)->elevation != -1)
			(*biome)->elevation = (double)(*biome)->elevation /
				              (double)max_alt * (double)100;
	}
}


void
MapBuild::CreateRivers()
{
	logger.Debug("Generating rivers...");

	int rivers_left = pars.n_rivers;

	while(rivers_left > 0)
	{
		int b = rand() % biomes.size();
		if(biomes[b]->terrain != t_WATER)
		{
			int k = rand() % biomes[b]->polygon->points.size();
			Point p = biomes[b]->polygon->points[k];
			if(DistanceFromWater(p, false) > 600)
			{
				CreateRiver(p);
				--rivers_left;
			}
		}
	}
}


void
MapBuild::CreateRiver(Point p)
{
	Polygon* river = new Polygon();
	rivers.push_back(river);

	while(p.elevation != -1)
	{
		river->points.push_back(p);
		
		// find neighbours
		std::vector<Point> neighbours;
		for(std::vector<Biome*>::const_iterator biome = biomes.begin();
				biome != biomes.end(); biome++)
			if((*biome)->polygon->ContainsPoint(p))
				(*biome)->polygon->NeighbourPoints(p, neighbours);
		assert(neighbours.size() > 0);

		// order by elevation
		std::sort(neighbours.begin(), neighbours.end(), 
				[](Point const& p1, Point const& p2) -> bool
				{ return p1.elevation < p2.elevation; });

		// skip points already added
		unsigned int n = 0;
		while(true)
		{
			p = neighbours[n];
			if(std::find(river->points.begin(), 
					river->points.end(), p) == 
					river->points.end())
				break;
			if(n >= neighbours.size())
				return;
			++n;
		}
	}
}


int 
MapBuild::DistanceFromWater(Point const& p, bool include_rivers)
{
	int dist = INT_MAX;

	// distance from sea
	for(std::vector<Biome*>::const_iterator biome = biomes.begin();
			biome != biomes.end(); biome++)
		if((*biome)->terrain == t_WATER)
		{
			std::vector<Point>::const_iterator point;
			for(point = (*biome)->polygon->points.begin(); 
				point != (*biome)->polygon->points.end(); 
				point++)
			{
				int new_dist = p.Distance(*point);
				if(new_dist < dist)
					dist = new_dist;
			}
		}

	/*
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

	*/
	assert(dist != INT_MAX);
	return dist;
}
