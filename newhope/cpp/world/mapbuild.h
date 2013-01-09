#ifndef MAPBUILD_H
#define MAPBUILD_H

#include <vector>

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

private:
	void CreatePolygons();

	struct MapParameters const& pars;
	std::vector<Biome*> biomes;
};

#endif
