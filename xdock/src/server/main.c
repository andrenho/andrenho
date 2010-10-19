#include <signal.h>
#include <stdlib.h>

#include "options.h"
#include "x11.h"
#include "network.h"

// catch quit signal
void quit(int sig)
{
	(void) sig;
	net_quit();
	x11_quit();
	exit(0);
}

// main procedure
int main(int argc, char* argv[])
{
	// parse arguments
	opt_parse(argc, argv);

	// create window
	x11_initialize();

	// initialize signal
	signal(SIGINT, quit);

	// start the network and listen to the clients
	net_startup();

	return 0;
}
