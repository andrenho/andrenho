#ifndef BUILDING_H
#define BUILDING_H

#include <string>
using namespace std;

class Building
{
public: 
	Building(int x, int y, int w, int h)
		: x(x), y(y), w(w), h(h) { }
	
	virtual bool IsWorkplace() { return false; }

	virtual string Name() = 0;

	const int x, y, w, h;
};

#endif
