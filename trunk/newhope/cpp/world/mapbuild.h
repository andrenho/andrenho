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
	explicit MapBuild(const MapParameters& pars);
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
	void ConnectClusters(std::vector<const City*> const& c1, 
			std::vector<const City*> const& c2);
	void FindCityCluster(const City* city, std::vector<const City*>& cs);
	void CreateRoad(const City& c1, const City& c2);
	Polygon* CreateFlow(Point<int> start, int iterations=INT_MAX);
	int DistanceFromWater(Point<int> const& p, bool include_rivers);
	bool AreNeighbours(const Biome& b1, const Biome& b2);
	void BiomeNeighbours(const Biome& biome, 
			std::vector<const Biome*>& biomes);

	const MapParameters& pars;

	DISALLOW_COPY_AND_ASSIGN(MapBuild);
};

#endif
