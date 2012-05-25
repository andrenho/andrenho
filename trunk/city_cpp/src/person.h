#ifndef PERSON_H
#define PERSON_H

class Person
{
public:
	Person(float x, float y)
		: x(x), y(y) { }

	float X() const { return x; }
	float Y() const { return y; }

protected:
	float x, y;
};

#endif
