#include "options.h"
#include "network.h"
#include "window.h"

int main(int argc, char* argv[])
{
	// parse arguments
	opt_parse(argc, argv);

	// create window
	win_create();

	// start the network and listen to the clients
	net_startup();

	// parse user events
	win_loop_events();

	return 0;
}
