#include "world/person.h"

#include "util/logger.h"

Person::~Person()
{
}


void
Person::Process()
{
	if(!(mov_x == 0 && mov_y == 0)) {
		Pos.x += mov_x / 4.0;
		Pos.y += mov_y / 4.0;
		++step;
	}
}


void 
Person::Movement(int x, int y)
{
	if(mov_x == x && mov_y == y) {
		return;
	}

	mov_x = x; 
	mov_y = y;
	step = 0;

	if(x == 1) {
		Facing = 'e';
	} else if(x == -1) {
		Facing = 'w';
	} else if(y == 1) {
		Facing = 's';
	} else if(y == -1) {
		Facing = 'n';
	}
}
