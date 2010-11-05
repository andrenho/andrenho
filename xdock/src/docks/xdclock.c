#include <xdock.h>
#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#if !_WIN32 && !__CYGWIN__
#  include <sys/sysinfo.h>
#endif

#define VERSION "0.1"

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

static char* pm_xpm[] = {
"11 6 3 1",
" 	s panel_bg",
".	s unlit",
"x	s lit",
"  .   xxxx ",
" . .  x   x",
" . .  x   x",
"..... xxxx ",
".   . x    ",
".   . x    " };

static int hour_system = 24;
static int show_date = 1;
static int show_seconds = 0;
static int uptime = 0;

static void show_help(FILE* f)
{
	fprintf(f,"\
Usage: xdclock [OPTION]...\n\
Clock applet to display the date/hour using xdock.\n\
\n\
All arguments are optional.\n\
  -c, --clock=VALUE             Choose between 12-hour or 24-hour clock\n\
                                (possible values: 12 or 24).\n\
  -n, --no-date                 Don't display the date.\n\
  -d, --seconds                 Display the seconds in the clock.\n\
  -u, --uptime                  Display uptime instead of current time.\n\
  -s, --server                  Server address (default: localhost).\n\
  -p, --port                    Server port (default: 52530).\n\
  -h, --help                    This help message.\n\
  -V, --version                 The application version.\n");
}


static void show_version()
{
	printf("xdclock version " VERSION "\n");
	exit(0);
}


static char* upcase(char* str)
{
	char* i;
	for(i=str; i[0]; i[0] = toupper(i[0]), i++);
	return str;
}


static int make_display(char* hour, char* seconds, char* date)
{
	time_t t;
	struct tm *tmp;
	t = time(NULL);
	tmp = localtime(&t);

#if !_WIN32 && !__CYGWIN__
	if(uptime)
	{
		struct sysinfo info;
		sysinfo(&info);
		int updays = (int)info.uptime / (60*60*24);
		int upminutes = (int)info.uptime / 60;
		int uphours = (upminutes / 60) % 24;
		upminutes %= 60;
		int upseconds = info.uptime % 60;
		sprintf(hour, "%2d:%02d", uphours, upminutes);
		sprintf(seconds, "%02d", upseconds);
		sprintf(date, "%3d DAY%s UP  ", updays, updays != 1 ? "S" : "");
		return 0;
	}
	else
#endif
	{
		strftime(hour, 6, hour_system == 24 ? "%k:%M" : "%l:%M", tmp);
		strftime(seconds, 3, "%S", tmp);
		strftime(date, 25, "%d %b %Y",tmp);
		upcase(date);

		char tm[3];
		strftime(tm, 3, "%P", tmp);
		return !strcmp(tm, "pm");
	}
}


static void parse_arguments(int argc, char* argv[])
{
	int c;
	while(1)
	{
		static struct option long_options[] = {
			{ "clock",	required_argument, 0, 'c' },
			{ "no-date",    no_argument,	   0, 'n' },
			{ "seconds",	no_argument,	   0, 'd' },
			{ "uptime",	no_argument,	   0, 'u' },
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
			case 'c':
				if(!strcmp(optarg, "24"))
					hour_system = 24;
				else if(!strcmp(optarg, "12"))
					hour_system = 12;
				else
				{
					fprintf(stderr, "Accepted values for "
							"clock: 12 or 24.\n");
					exit(EXIT_FAILURE);
				}
				break;

			case 'n':
				show_date = 0;
				break;

			case 'd':
				show_seconds = 1;
				break;

			case 'u':
#if !_WIN32 && !__CYGWIN__
				fprintf(stderr, "Uptime is not supported on "
						"Windows.\n");
				exit(EXIT_FAILURE);
#endif
				uptime = 1;
				break;

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


int main(int argc, char* argv[])
{
	char hour[6], seconds[3], date[25];

	// parse arguments
	parse_arguments(argc, argv);

	// calculate position
	int hour_x = (show_seconds || (hour_system == 12) ? 14 : 22);
	int hour_y = (show_date ? 29 : 36);

	// open connection
	XD_Connection *cn = xd_connect(argc, argv, "CLOCK");
	if(!cn)
		return 1;
	xd_send_xpm(cn, "AM", am_xpm);
	xd_send_xpm(cn, "PM", pm_xpm);

	// draw panel
	xd_panel(cn, 4, 4, 88, 88);

	for(;;)
	{
		// query time
		int pm = make_display(hour, seconds, date);

		// draw hours
		xd_write(cn, "led20", hour_x, hour_y, hour);
		if(strtol(seconds, NULL, 10) % 2 == 1)
			xd_box(cn, "panel_bg", hour_x+25, hour_y+3, 3, 12);

		// draw seconds
		if(show_seconds)
			xd_write(cn, "led9", hour_x+55, hour_y+11, seconds);

		// draw AM/PM
		if(hour_system == 12 && !uptime)
			xd_draw_image(cn, pm ? "PM" : "AM", hour_x+56, hour_y+1);

		// draw date
		if(show_date || uptime)
			xd_write(cn, "led7", 16 - (uptime ? 6 : 0), 
					hour_y+30, date);

		xd_update(cn);
		usleep(1000000);
	}
}
