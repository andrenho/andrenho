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
	
	bool IsWorkplace() { return true; }
	const vector<Person*> Workers() const { return workers; }
	void Hire(Person* p);
	

protected:
	vector<Person*> workers;
};

#endif
