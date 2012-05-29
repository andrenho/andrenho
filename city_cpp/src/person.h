#ifndef PERSON_H
#define PERSON_H

#include <vector>
#include <string>
using namespace std;

#include "psyche.h"
#include "goal.h"
class City;

class Person
{
public:
	Person(float x, float y);
	void Step();
	void ReceiveMoney(int amount);
	void LookForJob();

	int Health() const;
	bool HasJob() const;
	float X() const { return x; }
	float Y() const { return y; }
	int Money() const { return money; }
	int Stamina() const { return stamina; }

	const string name, surname;
	City* city;

protected:
	Psyche psyche;
	float x, y;
	int money;
	int stamina;
	Goal goal;

	void MakePlan();
};

#endif
