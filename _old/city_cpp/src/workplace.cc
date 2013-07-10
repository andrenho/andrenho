#include "workplace.h"

#include "person.h"
#include "debug.h"

void
Workplace::Hire(Person* p)
{
	debug << p->Name() << " was hired by " << Name() << "." << endl;
}
