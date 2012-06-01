#ifndef WORKPLACE_H
#define WORKPLACE_H

#include <vector>
using namespace std;

#include "building.h"

class Person;

class Workplace : public Building
{
public:
	Workplace(int x, int y, int w, int h)
		: Building(x, y, w, h) { }
	virtual ~Workplace() { }
	
	bool IsWorkplace() { return true; }
	void Hire(Person* p);
	
	vector<Person*> Workers;
};

#endif
