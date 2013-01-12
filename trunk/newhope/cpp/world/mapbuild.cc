#include "world/mapbuild.h"

#include <cassert>
#include <algorithm>
#include <vector>

#include "util/logger.h"
#include "util/polygon.h"
#include "world/biome.h"
#include "world/city.h"

MapBuild::MapBuild(struct MapParameters const& pars)
	: pars(pars)
{
	CreatePolygons();
	CreateCoastline();
	CreateLakes();
	CreateElevation();
	CreateRivers();
	CreateMoisture();
	CreateLava();
	CreateBiomes();
	CreateCities();
}


MapBuild::~MapBuild()
{
	for(const auto& city : cities)
		delete city;
	for(const auto& river : rivers)
		delete river;
	for(const auto& biome : biomes)
		delete biome;
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
	polygon.MidlineDisplacement(4);
	for(const auto& biome : biomes)
	{
		Point p = biome->polygon->Midpoint();
		if(!polygon.PointInPolygon(p))
			biome->terrain = t_WATER;
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
		for(const auto& biome : biomes)
		{
			Point p = biome->polygon->Midpoint();
			if(lake.PointInPolygon(p))
				biome->terrain = t_WATER;
		}
	}
}


void
MapBuild::CreateElevation()
{
	logger.Debug("Generating map elevation...");

	// set water elevation
	for(const auto& biome : biomes)
		if(biome->terrain == t_WATER)
		{
			for(const auto& point : biome->polygon->points)
				point.elevation = -1;
			biome->elevation = -1;
		}

	// set other tiles elevation
	int max_alt = 0;
	for(const auto& biome : biomes)
		if(biome->terrain != t_WATER)
		{
			int tot_alt = 0;
			for(const auto& point : biome->polygon->points)
			{
				point.elevation = DistanceFromWater(
						point, false);
				point.elevation += rand() % 200;
				tot_alt += point.elevation;
				max_alt = std::max(max_alt, point.elevation);
			}
			biome->elevation = tot_alt / 
				biome->polygon->points.size();
		}
	
	// normalize elevation
	for(const auto& biome : biomes)
	{
		if(biome->elevation != -1)
			biome->elevation = (double)biome->elevation /
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
		for(const auto& biome : biomes)
			if(biome->polygon->ContainsPoint(p))
				biome->polygon->NeighbourPoints(p, neighbours);
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
			logger.Debug("repeat!");
			++n;
		}
	}
}


void 
MapBuild::CreateMoisture()
{
	logger.Debug("Generating moisture...");

	// generate moisture
	int max_moi = 0;
	for(const auto& biome : biomes)
		if(biome->terrain == t_WATER)
			biome->moisture = 0;
		else
		{
			int tot_moi = 0;
			for(const auto& point : biome->polygon->points)
			{
				int moi = DistanceFromWater(point, true);
				tot_moi += moi;
				max_moi = std::max(max_moi, moi);
			}
			biome->moisture = tot_moi / 
				biome->polygon->points.size();
		}
	
	// normalize moisture
	for(const auto& biome : biomes)
	{
		biome->moisture = 100 - ((double)biome->moisture /
			              (double)max_moi * (double)100);
	}
}


void
MapBuild::CreateLava()
{
}


void
MapBuild::CreateBiomes()
{
	/*
	 * Elev/Moist   0-30       30-60      60-100
	 *  0-30        DIRT       EARTH      GRASS
	 * 30-60        ROCK       GRASS      HOTFOREST
	 * 60-100       LAVAROCK   SNOW       COLDFOREST
	 */
	for(const auto& biome : biomes)
	{
		if(biome->terrain == t_WATER)
			continue;

		int alt = biome->elevation;
		int moi = biome->moisture;
		TerrainType t = t_DIRT;
		if(alt < 20)
			t = t_DIRT;
		else if(alt < 40)
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
		biome->terrain = t;
	}
}


void
MapBuild::CreateCities()
{
	for(int i=0; i<pars.n_cities; i++)
	{
		// check if it's not in the sea
		int b;
try_again:
		do 
		{
			b = rand() % biomes.size();
		} while(biomes[b]->terrain == t_WATER);

		// check if neighbours don't have a city already
		std::vector<Biome const*> neighbours;
		BiomeNeighbours(*biomes[b], neighbours);
		for(auto const& neigh: neighbours)
			if(neigh->has_city)
				goto try_again;

		// add city
		Point pos = biomes[b]->polygon->Midpoint();
		cities.push_back(new City(pos));
		biomes[b]->has_city = true;
	}
}


int 
MapBuild::DistanceFromWater(Point const& p, bool include_rivers)
{
	int dist = INT_MAX;

	// distance from sea
	for(const auto& biome : biomes)
		if(biome->terrain == t_WATER)
		{
			for(const auto& point : biome->polygon->points)
			{
				int new_dist = p.Distance(point);
				if(new_dist < dist)
					dist = new_dist;
			}
		}

	// distance from a river
	if(include_rivers)
		for(const auto& river : rivers)
			for(const auto& point : river->points)
			{
				int new_dist = point.Distance(p);
				if(new_dist < dist)
					dist = new_dist;
			}

	assert(dist != INT_MAX);
	return dist;
}


bool 
MapBuild::AreNeighbours(Biome const& b1, Biome const& b2)
{
	std::vector<Biome const*> neigh;
	BiomeNeighbours(b1, neigh);
	return std::find(neigh.begin(), neigh.end(), &b2) != neigh.end();
}


void 
MapBuild::BiomeNeighbours(Biome const& biome, std::vector<Biome const*>& biomes)
{
	for(auto const& b: this->biomes)
		if(biome.polygon->IsTouching(*b->polygon) && &biome != b)
			biomes.push_back(b);
}
