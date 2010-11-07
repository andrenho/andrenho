#include <xdock.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

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


static int calendar_data(char* month_year, char days[35][3])
{
	// get days
	int i;
	time_t t;
	struct tm *tmp;
	t = time(NULL);
	tmp = localtime(&t);

	// get month
	strftime(month_year, 19, "%b %Y", tmp);
	upcase(month_year);

	// get days
	struct tm tm = { 0, 0, 0, 1, tmp->tm_mon, tmp->tm_year, 0, 0, 0 };
	mktime(&tm);
	int max_d, d = 1;
	if(tmp->tm_mon == 2)
		max_d = 28;
	else if(tmp->tm_mon == 4 || tmp->tm_mon == 6 || tmp->tm_mon == 9
	||      tmp->tm_mon == 11)
		max_d = 30;
	else
		max_d = 31;
	int today = -1;
	for(i=0; i<35; i++)
		if(i<tm.tm_wday || d > max_d)
			strcpy(days[i], "  ");
		else
		{
			if(d == tmp->tm_mday && tm.tm_mon == tmp->tm_mon
			&& tm.tm_year == tmp->tm_year)
				today = i;
			sprintf(days[i], "%2d", d++);
		}
	return today;
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
	char* weekdays[] = { "SU", "MO", "TU", "WE", "TH", "FR", "SA" };
	char days[35][3];
	int today = calendar_data(month_year, days);

	// draw panel
	xd_panel(cn, 4, 4, 88, 88);

	// draw calendar
	xd_write(cn, "led7", (96/2) - (strlen(month_year) * 3), 10, month_year);
	xd_line(cn, "halflit", 10, 21, 86, 21);

	int i;
	for(i=0; i<7; i++)
		xd_write(cn, "led5_l", (i+1) * 12 - 4, 29, weekdays[i]);

	int x, y, n=0;
	for(y=0; y<5; y++)
		for(x=0; x<7; x++)
		{
			if(n == today)
				xd_rectangle(cn, "lit", x * 12 + 5, 
						(y * 10) +37, 12, 10);
			xd_write(cn, "led5_l", x * 12 + 7, (y * 10) +40, days[n++]);
		}

	xd_update(cn);

	for(;;)
	{
		usleep(1000000);
	}
}
