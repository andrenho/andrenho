#ifndef WORLD_PERSON_H
#define WORLD_PERSON_H

#include "util/defines.h"
#include "util/point.h"
class World;

class Person {
public:
	Person(const World& world, Point<double> pos)
		: Pos(pos), Facing('s'), world(world), mov_x(0), mov_y(0),
	          step(0) { }
	~Person();

	void Process();
	void Movement(int x, int y);

	inline int Step() const { return step; }

	Point<double> Pos;
	char Facing;

private:
	const World& world;
	int mov_x, mov_y;
	int step;

	DISALLOW_COPY_AND_ASSIGN(Person);
};

#endif
