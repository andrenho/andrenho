#ifndef CITY_H
#define CITY_H

#include <vector>
using namespace std;

#include "building.h"
#include "person.h"

class Workplace;

class City
{
public:
	City();
	~City();

	void Step();
	void Build(Building* b);
	void ReceiveImmigrant(Person* p);
	bool FindJobForPerson(Person* p);

	const vector<Building*>* Buildings() const { return &buildings; }
	const vector<Person*>* People() const { return &people; }

private:
	vector<Building*> buildings;
	vector<Person*> people;

	int JobScore(Workplace* workplace, Person* p);
};

#endif
