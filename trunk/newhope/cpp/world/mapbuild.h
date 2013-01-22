#ifndef MAPBUILD_H
#define MAPBUILD_H

#include <climits>
#include <vector>
#include <map>

#include "util/defines.h"
#include "util/point.h"

class Biome;
class City;
class Polygon;

struct MapParameters {
	unsigned int seed;
	int w, h;
	int n_rivers;
	int n_cities;
	int n_roads;
};


class MapBuild {
public:
	explicit MapBuild(struct MapParameters const& pars);
	~MapBuild();

	std::vector<Biome*> biomes;
	std::vector<Polygon*> rivers;
	std::vector<Polygon*> lava;
	std::vector<Polygon*> roads;
	std::vector<City*> cities;

private:
	void CreatePolygons();
	void CreateCoastline();
	void CreateLakes();
	void CreateElevation();
	void CreateRivers();
	void CreateMoisture();
	void CreateLava();
	void CreateBiomes();
	void CreateCities();
	void CreateRoads();
	//void FindNations();

	void FindUnconnectedCities();
	void ConnectClusters(std::vector<City const*> const& c1, 
			std::vector<City const*> const& c2);
	void FindCityCluster(City const* city, std::vector<City const*>& cs);
	void CreateRoad(City const& c1, City const& c2);
	Polygon* CreateFlow(Point<int> start, int iterations=INT_MAX);
	int DistanceFromWater(Point<int> const& p, bool include_rivers);
	bool AreNeighbours(Biome const& b1, Biome const& b2);
	void BiomeNeighbours(Biome const& biome, 
			std::vector<Biome const*>& biomes);

	struct MapParameters const& pars;

	DISALLOW_COPY_AND_ASSIGN(MapBuild);
};

#endif
