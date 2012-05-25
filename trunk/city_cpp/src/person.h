#ifndef PERSON_H
#define PERSON_H

#include "psyche.h"

class Person
{
public:
	Person(float x, float y);

	float X() const { return x; }
	float Y() const { return y; }

protected:
	Psyche psyche;
	float x, y;
};

#endif
