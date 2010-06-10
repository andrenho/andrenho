#ifndef PERSON_H
#define PERSON_H


class Object
{
public:
	Object() : x(1.0f), y(1.0f) {}

	float x, y;

	virtual void Move() = 0;
};


class Person : public Object
{
public:
	void Move();
};

#endif
