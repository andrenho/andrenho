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

	std::vector<Biome*> biomes;
private:
	void CreatePolygons();
	void CreateCoastline();
	void CreateLakes();

	struct MapParameters const& pars;
};

#endif
