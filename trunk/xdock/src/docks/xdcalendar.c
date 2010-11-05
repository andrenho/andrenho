#include <xdock.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define VERSION "0.1"

static void show_help(FILE* f) // TODO
{
	fprintf(f,"\
Usage: XXXXXX [OPTION]...\n\
Description XXXXXXXXXXXXXXXXX...\n\
\n\
All arguments are optional.\n\
  -s, --server                  Server address (default: localhost).\n\
  -p, --port                    Server port (default: 52530).\n\
  -h, --help                    This help message.\n\
  -V, --version                 The application version.\n");
}


static void show_version()
{
	printf("XXXXXX version " VERSION "\n"); // TODO
	exit(0);
}


static char* upcase(char* str)
{
	char* i;
	for(i=str; i[0]; i[0] = toupper(i[0]), i++);
	return str;
}


static void parse_arguments(int argc, char* argv[])
{
	int c;
	while(1)
	{
		static struct option long_options[] = {
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


static void calendar_data(char month_year[20], char weekdays[7],
		char days[35][3])
{
	strcpy(month_year, "MAY 2010");
	strcpy(weekdays, "STQQSSD");
	int i;
	for(i=0; i<35; i++)
		if(i<31)
			sprintf(days[i], "%2d", i+1);
		else
		{
			days[i][0] = ' ';
			days[i][1] = '\0';
		}
}


int main(int argc, char* argv[])
{
	// parse arguments
	parse_arguments(argc, argv);

	// open connection
	XD_Connection *cn = xd_connect(argc, argv, "CLOCK");
	if(!cn)
		return 1;

	char month_year[20];
	char weekdays[7];
	char days[35][3];
	calendar_data(month_year, weekdays, days);

	// draw panel
	xd_panel(cn, 4, 4, 88, 88);

	// draw calendar
	xd_write(cn, "led7", (96/2) - (strlen(month_year) * 3), 8, month_year);

	int i;
	for(i=0; i<7; i++)
	{
		char s[2];
		sprintf(s, "%c", weekdays[i]);
		xd_write(cn, "led7", (i+1) * 11 + 5, 20, s);
	}

	int x, y, n=0;
	for(y=0; y<5; y++)
		for(x=0; x<7; x++)
			xd_write(cn, "led7", x * 13 + 5, (y * 10) +30, days[n++]);

	xd_update(cn);

	for(;;)
	{
		usleep(1000000);
	}
}
