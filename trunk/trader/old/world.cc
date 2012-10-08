#include "world.h"

#include "player.h"
#include "city.h"

World::World()
	: player(player)
{
	City *c1 = new City(), *c2 = new City();
	c1->AddConnection(c2, 100);
	cities.push_back(c1);
	cities.push_back(c2);
}


World::~World()
{
}
