/* Main program file. Here is the server main loop.
 *
 * Author: André Wagner
 * This source file is covered by GNU Public License v.2. */

#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#include "options.h"
#include "x11.h"
#include "network.h"

static int running = 1; // True while the server is running.


// catch quit signal
void quit(int sig)
{
	(void) sig;
	running = 0;
}


// main procedure
int main(int argc, char* argv[])
{
	struct timeval start, end;

	// parse arguments
	opt_parse(argc, argv);

	// initialize connection to X11
	x11_initialize();

	// initialize the network
	net_startup();

	// setup a CTRL+C signal
	signal(SIGINT, quit);

	// main loop. It'll execute every 1/60 second.
	while(running)
	{
		gettimeofday(&start, NULL);

		// main loop functions
		net_check_for_clients();  // check if a new client has connected
		net_receive_data();       // receive data from clients
		x11_do_events();          // process X11 events

		// if 1/60 of a second hasn't passed yet, sleeps the program
		// until the time has completed.
		gettimeofday(&end, NULL);
		if(end.tv_usec - start.tv_usec < 1000000/60)
			usleep(1000000/60 - (end.tv_usec - start.tv_usec));
	}

	// The user pressed CTRL+C, quitting now...
	net_quit();
	x11_quit();
	return EXIT_SUCCESS;
}
