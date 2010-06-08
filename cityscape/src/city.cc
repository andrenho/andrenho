#include "city.h"

#include <cstdlib>

#include "person.h"

City::City(char* name, int w, int h)
	: name(name), w(w), h(h)
{
	tile = new Tile[w*h];
	for(int x=0; x<w; x++)
		for(int y=0; y<h; y++)
		{
			tile[y*w+x].x = x;
			tile[y*w+x].y = y;
		}

	people.push_back(new Person());
}


Tile*
City::getTile(int x, int y)
{
	if(x < 0 || x >= w || y < 0 || y >= h)
		return 0x0;
	else
		return &tile[y*w+x];
}


bool
City::BuildStructure(Structure* structure, int x, int y, bool turned,
		StructureInfo* info)
{
	structure->info = info;
	structure->x = x;
	structure->y = y;
	structure->turned = turned;

	// connect to tiles
	int w = turned ? info->h : info->w;
	int h = turned ? info->w : info->h;
	for(int xx=x; xx<x+w; xx++)
		for(int yy=y; yy<y+h; yy++)
		{
			Tile* t = getTile(xx, yy);
			if(!t || t->structure)
				return false;
			t->structure = structure;
		}

	return true;
}


bool
City::BuildResidence(int x, int y, bool turned,
		ResidentialInfo::Density density)
{
	ResidentialInfo* info;

	if(density == ResidentialInfo::LOW_D) // TODO
		info = LowLDResidenceE;
	else
		info = LowHDResidenceE;

	Residence* residence = new Residence(info);
	if(!BuildStructure(residence, x, y, turned, info))
	{
		delete residence;
		return false;
	}
	residence->occupants = 0;
	structures.push_back(residence);

	return true;
}
