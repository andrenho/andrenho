#ifndef PSYCHE_H
#define PSYCHE_H

class Person;

class Psyche
{
public:
	void Init(Person* person);

private:
	typedef enum {
		FOOD, SLEEP, HEALTH, MORALITY, MONEY, HOME, FUN, FRIENDS, FAMILY, RESPECT,
		ACHIEVEMENT, RELIGION, _END
	} Need;

	Person* person;

	Need UnachievedNeed();
	bool IsNeedFullfilled(Need need);
};

#endif
