#ifndef PSYCHE_H
#define PSYCHE_H

class Person;

class Psyche
{
public:
	void Init(Person* person);

	typedef enum {
		FOOD, SLEEP, HEALTH, MORALITY, EMPLOYMENT, HOME, FUN, FRIENDS, FAMILY, RESPECT,
		ACHIEVEMENT, RELIGION, _END
	} Need;
	Need UnachievedNeed();

private:
	Person* person;

	bool IsNeedFullfilled(Need need);
};

#endif
