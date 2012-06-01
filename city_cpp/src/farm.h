#ifndef FARM_H
#define FARM_H

#include "workplace.h"

class Farm : public Workplace
{
public:
	Farm(int x, int y, int w, int h)
		: Workplace(x, y, w, h) { }
	virtual string Name() { return "Farm"; }
};

#endif
