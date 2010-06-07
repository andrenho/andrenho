#ifndef GUI_H
#define GUI_H

#include "city.h"

class GUI
{
protected:
	City* city;

public:
	GUI(City* city) : city(city) { }

	virtual bool Startup() = 0;
	virtual void Main() = 0;
};

#endif
