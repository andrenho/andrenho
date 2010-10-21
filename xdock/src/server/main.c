#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

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
	struct timeval start, end;

	// parse arguments
	opt_parse(argc, argv);

	// create window
	x11_initialize();

	// initialize signal
	signal(SIGINT, quit);

	// initialize the network
	net_startup();

	// main loop
	for(;;)
	{
		gettimeofday(&start, NULL);

		// do events
		net_check_for_clients();
		net_receive_data();
		x11_do_events();

		// wait
		gettimeofday(&end, NULL);
		if(end.tv_usec - start.tv_usec < 1000/60)
			usleep(1000/60 - (end.tv_usec - start.tv_usec));
	}

	return 0;
}
