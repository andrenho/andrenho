#include <xdock.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define VERSION "0.1"

#define PROCESS_CHARS 10
#define TOP_PROCESSES 7

int warning = 80;

struct Process {
	char name[PROCESS_CHARS+1];
	float usage;
};
struct Usage {
	struct Process top[TOP_PROCESSES];
	int percent;
};

static char* am_xpm[] = {
"11 6 3 1",
" 	s panel_bg",
".	s unlit",
"x	s lit",
"  x   .... ",
" x x  .   .",
" x x  .   .",
"xxxxx .... ",
"x   x .    ",
"x   x .    " };


static void show_help(FILE* f)
{
	fprintf(f,"\
Usage: xdmemory [OPTION]...\n\
A dock that connects to xdockserver to display memory information.\n\
\n\
All arguments are optional.\n\
  -w, --warning [VALUE]         Warns about memory overuse starting in VALUE %.\n\
  -s, --server                  Server address (default: localhost).\n\
  -p, --port                    Server port (default: 52530).\n\
  -h, --help                    This help message.\n\
  -V, --version                 The application version.\n");
}


static void show_version()
{
	printf("xdmemory version " VERSION "\n");
	exit(0);
}


static void parse_arguments(int argc, char* argv[])
{
	int c;
	while(1)
	{
		static struct option long_options[] = {
			{ "warning",    required_argument, 0, 'w' },
			{ "server",     required_argument, 0, 's' },
			{ "port",       required_argument, 0, 'p' },
			{ "help",	no_argument,	   0, 'h' },
			{ "version",	no_argument,	   0, 'V' },
			{ 0, 0, 0, 0 }
		};
		int optidx = 0;
		c = getopt_long(argc, argv, "c:ndus:p:hV", long_options, &optidx);
		if(c == -1)
			break;

		switch(c)
		{
			case 'w':
				warning = strtol(optarg, NULL, 10);
				if(warning < 0 || warning > 100)
				{
					fprintf(stderr, "Warning value must be "
							"between 0 and 100.\n");
					exit(1);
				}
				break;

			case 's':
			case 'p':
				break; // parsed by the library

			case 'h':
				show_help(stdout);
				exit(EXIT_SUCCESS);

			case 'V':
				show_version();
				exit(EXIT_SUCCESS);
			
			case '?':
				show_help(stderr);
				exit(EXIT_FAILURE);

			default: abort();
		}
	}
	if(optind < argc)
	{
		show_help(stderr);
		exit(EXIT_FAILURE);
	}
}


void memory_usage(struct Usage *usage)
{
	// command = ps -eo %mem,comm --sort:-rss
	
	strcpy(usage->top[0].name, "CHROMIUM");
	usage->top[0].usage = 12.4;
	strcpy(usage->top[1].name, "XORG");
	usage->top[1].usage = 6.2;
	strcpy(usage->top[2].name, "INIT");
	usage->top[2].usage = 0.2;
	strcpy(usage->top[3].name, "TOP");
	usage->top[3].usage = 0.1;
	strcpy(usage->top[4].name, "MIGRATION");
	usage->top[4].usage = 0.0;
	strcpy(usage->top[5].name, "SSHD");
	usage->top[5].usage = 0.0;
	strcpy(usage->top[6].name, "AIO/0");
	usage->top[6].usage = 0.0;
	usage->percent = 86;
}


int main(int argc, char* argv[])
{
	// parse arguments
	parse_arguments(argc, argv);

	// open connection
	XD_Connection *cn = xd_connect(argc, argv, "CLOCK");
	if(!cn)
		return 1;

	for(;;)
	{
		// get memory usage
		struct Usage usage;
		memory_usage(&usage);

		// draw panel
		xd_panel(cn, 4, 4, 88, 88);

		// draw processes
		int i;
		for(i=0; i<TOP_PROCESSES; i++)
			xd_write(cn, "led7", 7, 7 + (i*9), "%-10s_%4.1f",
					usage.top[i].name, usage.top[i].usage);

		// draw graph
		int x;
		char* color;
		for(x=26; x<=88; x+=2)
		{
			if((x-26) < (usage.percent / 100.0 * 62))
			{
				if((x-26) >= (warning / 100.0 * 62))
					color = "warning";
				else
					color = "lit";
			}
			else
				color = "unlit";
			xd_line(cn, color, x, 73, x, 73+14);
		}

		xd_update(cn);
		usleep(1000000);
	}
}
