#ifndef CITY_H
#define CITY_H

#include <vector>

#include "tile.h"
#include "residence.h"

class City
{
public:
	City(char* name, int w, int h);

	char* name;
	int w, h;
	Tile* tile;
	std::vector<Structure*> structures;
	std::vector<Person*> people;

	bool BuildResidence(int x, int y, bool turned,
			ResidentialInfo::Density density);
	Tile* getTile(int x, int y);

private:
	bool BuildStructure(Structure* structure, int x, int y, bool turned,
		StructureInfo* info);
};

#endif
