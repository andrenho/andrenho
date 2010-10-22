#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#include "options.h"
#include "x11.h"
#include "network.h"

static int running = 1;

// catch quit signal
void quit(int sig)
{
	(void) sig;
	running = 0;
}

// catch the alarm signal
void loop(int sig)
{
	(void) sig;
	net_check_for_clients();
	net_receive_data();
	x11_do_events();
}

// main procedure
int main(int argc, char* argv[])
{
	// parse arguments
	opt_parse(argc, argv);

	// create window
	x11_initialize();

	// initialize the network
	net_startup();

	// initialize signal
	signal(SIGINT, quit);

#if _WIN32
	while(running)
	{
		loop(0);
		usleep(1000000/60);
	}

#else
	struct sigaction sa;
	struct itimerval timer;

	// configure signals to catch
	sigset_t mask, oldmask;
	sigfillset(&mask);
	sigdelset(&mask, SIGALRM);
	sigdelset(&mask, SIGINT);

	// configure timer
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &loop;
	sigaction(SIGALRM, &sa, NULL);
	timer.it_value.tv_sec = timer.it_interval.tv_sec = 0;
	timer.it_value.tv_usec = timer.it_interval.tv_usec = 1000000/60;
	setitimer(ITIMER_REAL, &timer, NULL);

	// main loop
	while(running)
		sigsuspend(&mask);
#endif

	// quit
	net_quit();
	x11_quit();

	return EXIT_SUCCESS;
}
