#include "ui.h"
#include "world.h"
#include "port.h"
#include "travel.h"

int game_active = 1;

int main()
{
	// initialization
	init_ui();
	World* world = init();

	// main loop
	while(game_active)
	{
		Port* destination = port(world);
		travel(world, destination);
	}

	// exit
	end_ui();
	cleanup();

	return 0;
}
