#include "world.h"

World* w;

int main()
{
	// initialize
	w = new World();
	
	// cleanup
	delete w;

	return 0;
}
