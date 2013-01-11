#ifndef MAPBUILD_H
#define MAPBUILD_H

#include <vector>
#include <map>

#include "util/polygon.h"

class Biome;

struct MapParameters {
	unsigned int seed;
	int w, h;
	int n_rivers;
	int n_cities;
	int n_roads;
};


class MapBuild {
public:
	MapBuild(struct MapParameters const& pars);
	~MapBuild();

	std::vector<Biome*> biomes;
	std::vector<Polygon*> rivers;

private:
	void CreatePolygons();
	void CreateCoastline();
	void CreateLakes();
	void CreateElevation();
	void CreateRivers();
	void CreateMoisture();
	void CreateLava();
	void CreateBiomes();

	void CreateRiver(Point p);
	int DistanceFromWater(Point const& p, bool include_rivers);

	struct MapParameters const& pars;
};

#endif
