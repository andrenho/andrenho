#ifndef BUILDING_H
#define BUILDING_H

class Building
{
public: 
	Building(int x, int y, int w, int h)
		: x(x), y(y), w(w), h(h) { }

	const int x, y, w, h;
};

#endif
