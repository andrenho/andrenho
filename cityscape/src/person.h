#ifndef PERSON_H
#define PERSON_H


class Object
{
public:
	Object() : x(0.0f), y(0.0f) {}

	float x, y;
};


class Person : public Object
{
};

#endif
