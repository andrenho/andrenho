#include "city.h"

#include <algorithm>
#include <map>

#include "debug.h"
#include "workplace.h"

City::City()
{
	debug << "Initializing city..." << endl;
}


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
	for(vector<Person*>::iterator pi = people.begin();
			pi != people.end(); pi++)
		(*pi)->Step();
}


void 
City::Build(Building* b)
{
	// TODO - check bounds, etc
	buildings.push_back(b);
	debug << b->Name() << " built in " << b->x << "," << b->y << "." << endl;
}


void 
City::ReceiveImmigrant(Person* p)
{
	people.push_back(p);
	p->city = this;
	debug << p->Name() <<" immigrates to the city." << endl;
}


bool 
City::FindJobForPerson(Person* p)
{
	// find all workplaces in the city
	map<Workplace*, int> workplaces;
	for(vector<Building*>::iterator it = buildings.begin(); 
			it != buildings.end(); it++)
	{
		if((*it)->IsWorkplace())
			workplaces[dynamic_cast<Workplace*>(*it)] = 0;
	}
	
	// give a score for each place
	if(workplaces.empty())
		return false;
	for(map<Workplace*, int>::iterator it = workplaces.begin();
			it != workplaces.end(); it++)
		it->second = JobScore(it->first, p);
	
	// find most suitable place
	struct comparer
	{
		static bool value(
				const std::pair<Workplace*, int>& lhs,
				const std::pair<Workplace*, int>& rhs)
		{
			return lhs.second < rhs.second;
		}
	};
	Workplace* found = std::max_element(
			workplaces.begin(), 
			workplaces.end(), 
			comparer::value)->first;
	if(workplaces[found] == -1)
		return false;

	// sign a contract between person and workplace
	found->Hire(p);
	return true;
}


int 
City::JobScore(Workplace* workplace, Person* p)
{
	// check if worker doesn't already works here
	if(find(workplace->Workers.begin(), 
				workplace->Workers.end(), 
				p) != workplace->Workers.end())
		return -1;

	return 0;
}
