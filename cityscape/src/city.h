#ifndef CITY_H
#define CITY_H

#include <vector>

#include "tile.h"
#include "structure.h"

class City
{
public:
	City(char* name, int w, int h);

	char* name;
	int w, h;
	Tile* tile;
	std::vector<Structure*> structures;

	bool BuildResidence(int x, int y, bool turned, 
			ResidentialInfo::Level level, 
			ResidentialInfo::Density density);
	Tile* getTile(int x, int y);

private:
	bool BuildStructure(Structure* structure, int x, int y, bool turned, 
		StructureInfo* info);
};

#endif
