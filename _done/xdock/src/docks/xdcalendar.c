#include <xdock.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define VERSION "0.1"

struct tm *today, 	// timestamp for today
	  *selected;	// timestamp for the selected month

static char* xpm_left[] = {
"4 7 2 1",
" 	s panel_bg",
"o	s lit",
"   o",
"  oo",
" ooo",
"oooo",
" ooo",
"  oo",
"   o" };

static char* xpm_right[] = {
"4 7 2 1",
" 	s panel_bg",
"o	s lit",
"o   ",
"oo  ",
"ooo ",
"oooo",
"ooo ",
"oo  ",
"o   " };


static void show_help(FILE* f)
{
	fprintf(f,"\
Usage: xdcalendar [OPTION]...\n\
Create a calendar xdock.\n\
\n\
All arguments are optional.\n\
  -s, --server                  Server address (default: localhost).\n\
  -p, --port                    Server port (default: 52530).\n\
  -h, --help                    This help message.\n\
  -V, --version                 The application version.\n");
}


static void show_version()
{
	printf("xdcalendar version " VERSION "\n"); // TODO
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

	// get month
	strftime(month_year, 19, "%b %Y", selected);
	upcase(month_year);

	// get last day of the month
	int max_d, d = 1;
	if(selected->tm_mon == 2)
		max_d = 28;
	else if(selected->tm_mon == 3 || selected->tm_mon == 5 
	|| selected->tm_mon == 8 || selected->tm_mon == 10)
		max_d = 30;
	else
		max_d = 31;

	// get days
	int current_day = -1;
	for(i=0; i<35; i++)
		if(i < selected->tm_wday || d > max_d)
			strcpy(days[i], "  ");
		else
		{
			if(d == today->tm_mday 
			&& today->tm_mon == selected->tm_mon
			&& today->tm_year == selected->tm_year)
				current_day = i;
			sprintf(days[i], "%2d", d++);
		}
	return current_day;
}


int main(int argc, char* argv[])
{
	// parse arguments
	parse_arguments(argc, argv);

	// open connection
	XD_Connection *cn = xd_connect(argc, argv, "CLOCK");
	if(!cn)
		return 1;

	// send images
	xd_send_xpm(cn, "left", xpm_left);
	xd_send_xpm(cn, "right", xpm_right);

	// TODO - if it is a new day, change the day on the calendar

	// get TODAY and set as the selected month
	time_t t = time(NULL);
	today = localtime(&t);
#if _WIN32 // hack for mingw bug
	void* tmp = malloc(sizeof(struct tm));
	memcpy(tmp, today, sizeof(struct tm));
#endif
	selected = malloc(sizeof(struct tm));
	memset(selected, 0, sizeof(struct tm));
	selected->tm_mday = 1;
	selected->tm_mon = today->tm_mon;
	selected->tm_year = today->tm_year;
	mktime(selected);
#if _WIN32 // hack for mingw bug
	memcpy(today, tmp, sizeof(struct tm));
#endif

	// get info to create the calendar month
	char month_year[20];
	char* weekdays[] = { "SU", "MO", "TU", "WE", "TH", "FR", "SA" };
	char days[35][3];

	// main loop
	for(;;)
	{
		XD_Event e;
		int current_day = calendar_data(month_year, days);

		// draw panel
		xd_panel(cn, 4, 4, 88, 88);

		// draw calendar
		// month
		xd_write(cn, "led7", (96/2) - (strlen(month_year) * 3), 10, 
				month_year);
		xd_draw_image(cn, "left", 10, 10);
		xd_draw_image(cn, "right", 82, 10);
		xd_line(cn, "halflit", 10, 21, 86, 21);

		// weekdays
		int i;
		for(i=0; i<7; i++)
			xd_write(cn, "led5_l", (i+1) * 12 - 4, 29, weekdays[i]);

		// days
		int x, y, n=0;
		for(y=0; y<5; y++)
			for(x=0; x<7; x++)
			{
				if(n == current_day)
					xd_rectangle(cn, "lit", x * 12 + 5, 
							(y * 10) +37, 12, 10);
				xd_write(cn, "led5_l", x * 12 + 7, (y * 10) +40, 
						days[n++]);
			}

		xd_update(cn);

		// events
		xd_wait_event(cn, &e);
		if(e.type == MOUSE_DOWN 
		&& (e.x > 4 && e.x < 92 && e.y > 4 && e.y < 92))
		{
			int m = selected->tm_mon,
			    y = selected->tm_year;
			if(e.x < 96/2)
			{
				m--;
				if(m == 0)
				{
					m = 12;
					y--;
				}	
			}
			else
			{
				m++;
				if(m > 12)
				{
					m = 1;
					y++;
				}
			}
			selected = &(struct tm) { 0, 0, 0, 1, m, y, 0, 0, 0 };
			mktime(selected);
#if _WIN32 // hack for mingw bug
			memcpy(today, tmp, sizeof(struct tm));
#endif
		}
	}
}
