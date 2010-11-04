#include <xdock.h>
#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#if !_WIN32 && !__CYGWIN__
#  include <sys/sysinfo.h>
#endif

#define VERSION "0.1"

char date_format[30];
int hour_system = 24;
int show_date = 1;
int show_seconds = 1;
int uptime = 0;

static void show_help(FILE* f)
{
	fprintf(f,"\
Usage: xdclock [OPTION]...\n\
Clock applet to display the date/hour using xdock.\n\
\n\
All arguments are optional.\n\
  -f, --date-format=FORMAT      Use a date format, according to the formats in\n\
                                strftime.\n\
  -h, --hour=VALUE              Choose between 12-hour or 24-hour clock\n\
                                (possible values: 12 or 24).\n\
  -n, --no-date                 Don't display the date.\n\
  -s, --seconds                 Display the seconds in the clock.\n\
  -u, --uptime                  Display uptime instead of current time.\n");
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


void make_display(char* hour, char* seconds, char* date)
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
		int uphours = (updays * (60*60*24)) - (int)info.uptime / (60*60);
		int upminutes = (uphours * (60*60)) - (int)info.uptime / 60;
		int upseconds = (upminutes * 60) - (int)info.uptime;
		sprintf(hour, "%d:%d", uphours, upminutes);
		sprintf(seconds, "%d", upseconds);
		sprintf(date, "%d DAYS", updays);
	}
	else
#endif
	{
		strftime(hour, 6, hour_system == 24 ? "%H:%M" : "%I:%M", tmp);
		strftime(seconds, 3, "%S", tmp);
		strftime(date, 25, "%d %b %Y",tmp);
		upcase(date);
	}
}


int main(int argc, char* argv[])
{
	char hour[6], seconds[3], date[25];

	// calculate position
	int hour_x = show_seconds ? 14 : 22;
	int hour_y = show_date ? 29 : 36;
	
	// open connection
	XD_Connection *cn = xd_connect(argc, argv, "HELLO");
	if(!cn)
		return 1;

	// draw panel
	xd_panel(cn, 4, 4, 88, 88);
	
	for(;;)
	{
		make_display(hour, seconds, date);
		xd_write(cn, "led20", hour_x, hour_y, hour);
		if(show_seconds)
			xd_write(cn, "led9", hour_x+55, hour_y+11, seconds);
		if(show_date)
			xd_write(cn, "led7", 16, hour_y+30, date);
		xd_update(cn);
		usleep(1000000);
	}
}
