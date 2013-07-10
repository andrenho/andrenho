#ifndef CITY_H
#define CITY_H

#include <vector>
using namespace std;

class City;

class Connection
{
public:
	Connection(City* city, float distance)
		: city(city), distance(distance) { }

	City* city;
	float distance;
};


class City
{
public:
	void AddConnection(City* city, float distance);

	vector<Connection> connections;
};

#endif
