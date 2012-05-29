#include "person.h"

Person::Person(float x, float y)
	: name("John"), surname("Smith"), x(x), y(y), money(100), stamina(10), 
	  goal(DO_NOTHING)
{
	psyche.Init(this);
}


void
Person::Step()
{
	switch(goal)
	{
		case FIND_JOB:
			LookForJob();
			break;
		case DO_NOTHING:
			MakePlan();
			break;
		default:
			break;
	}
}


void
Person::MakePlan()
{
	Psyche::Need unachieved = psyche.UnachievedNeed();
	switch(unachieved)
	{
		case Psyche::EMPLOYMENT:
			goal = FIND_JOB;
			break;
		default:
			break;
	}
}


void
Person::LookForJob()
{
}


void 
Person::ReceiveMoney(int amount)
{
	this->money += amount;
}


int 
Person::Health() const
{
	return 10;
}


bool
Person::HasJob() const
{
	return false;
}
