#ifndef WORLD_PERSON_H
#define WORLD_PERSON_H

#include "util/point.h"
class World;

class Person {
public:
	Person(World const& world, Point pos)
		: Pos(pos), Facing('s'), world(world) { }
	virtual ~Person();

	Point Pos;
	char Facing;

private:
	World const& world;
};

#endif
