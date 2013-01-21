#ifndef WORLD_PERSON_H
#define WORLD_PERSON_H

#include "util/point.h"
class World;

class Person {
public:
	Person(World const& world, DPoint pos)
		: Pos(pos), Facing('s'), world(world), mov_x(0), mov_y(0),
	          step(0) { }
	virtual ~Person();

	void Process();
	void Movement(int x, int y);

	inline int Step() const { return step; }

	DPoint Pos;
	char Facing;

private:
	World const& world;
	int mov_x, mov_y;
	int step;
};

#endif
