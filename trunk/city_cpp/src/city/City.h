#ifndef CITY_H
#define CITY_H

#include <vector>
#include "city/Person.h"
#include "city/Building.h"

using namespace std;

class City
{
public:
    City();

    virtual void Process();
  
    vector<Person> people;
    vector<Building> buildings;
};

#endif
