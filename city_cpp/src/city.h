#ifndef CITY_H
#define CITY_H

#include <vector>
using namespace std;

#include "building.h"
#include "person.h"

class City
{
public:
	~City();

	void Step();
	void Build(Building* b);
	void ReceiveImmigrant(Person* p);

	const vector<Building*>* Buildings() const { return &buildings; }
	const vector<Person*>* People() const { return &people; }

private:
	vector<Building*> buildings;
	vector<Person*> people;
};

#endif
