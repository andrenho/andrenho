#include <signal.h>

#include "options.h"
#include "network.h"
#include "window.h"

// catch quit signal
void quit(int sig)
{
	net_quit();
	wm_quit();
}


// main procedure
int main(int argc, char* argv[])
{
	// parse arguments
	opt_parse(argc, argv);

	// create window
	wm_create();

	// initialize signal
	signal(SIGINT, quit);

	// start the network and listen to the clients
	net_startup();

	return 0;
}
