#ifndef WORLD_H
#define WORLD_H

#include <vector>
using namespace std;

class Player;
class City;

class World {
public:
	World();
	~World();

	Player& player;
	vector<City*> cities;
};

extern World* w;

#endif
