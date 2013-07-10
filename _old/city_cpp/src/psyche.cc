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
		// check if the person has enough money to buy a snack
		return (person->Money() > 3);
	case SLEEP:
		return (person->Stamina() > 0);
	case HEALTH:
		return (person->Health() >= 3);
	case MORALITY:
		return true; // ???
	case EMPLOYMENT:
		return person->HasJob();
	default:
		return true;
	}
}
