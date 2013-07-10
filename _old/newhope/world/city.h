#ifndef CITY_H
#define CITY_H

struct World;

typedef struct City {
	struct World* world;
	int x, y;
} City;

City* city_init(struct World* world, int x, int y);
void free_city(City* city);

#endif
