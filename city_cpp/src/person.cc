#include "person.h"

Person::Person(float x, float y)
	: x(x), y(y)
{
	psyche.Init(this);
}
