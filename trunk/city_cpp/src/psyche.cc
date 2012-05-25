#include "psyche.h"

#include "person.h"

void 
Psyche::Init(Person* person)
{
	this->person = person;
}


Psyche::Need 
Psyche::UnachievedNeed()
{
	for(int i=FOOD; i<_END; i++)
		if(!IsNeedFullfilled(static_cast<Need>(i)))
			return static_cast<Need>(i);
	return _END;
}


bool 
Psyche::IsNeedFullfilled(Psyche::Need need)
{
	switch(need)
	{
	case FOOD:
		return false;
	default:
		return true;
	}
}
