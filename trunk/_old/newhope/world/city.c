#include "city.h"

#include <stdlib.h>

#include "world/world.h"


City* city_init(World* world, int x, int y)
{
	City* city = calloc(sizeof(City), 1);
	city->x = x;
	city->y = y;
	city->world = world;
	return city;
}


void free_city(City* city)
{
	free(city);
}
