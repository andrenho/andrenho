#include "city.h"


City::~City()
{
	for(vector<Building*>::iterator bi = buildings.begin();
			bi != buildings.end(); bi++)
		free(*bi);
	for(vector<Person*>::iterator pi = people.begin();
			pi != people.end(); pi++)
		free(*pi);
}


void
City::Step()
{
}


void 
City::Build(Building* b)
{
	// TODO - check bounds, etc
	buildings.push_back(b);
}


void 
City::ReceiveImmigrant(Person* p)
{
	people.push_back(p);
}
