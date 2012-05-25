#include "city.h"
#include "ui.h"
#include "SDL.h"

#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
	City city;
	UI ui(city);

	city.Build(new Building(1, 1, 4, 4));

	Person* p = new Person(0.5, 0.5);
	city.ReceiveImmigrant(p);

	try
	{
		ui.Init();
	}
	catch(string e)
	{
		cerr << "Error initializing SDL: " << e << endl;
		return 1;
	}

	while(ui.Active())
	{
		ui.Draw();
		ui.Input();
		city.Step();
		ui.Wait();
	}

	return 0;
}
