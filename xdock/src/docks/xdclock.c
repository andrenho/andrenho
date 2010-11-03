#include <xdock.h>
#include <stdio.h>
#include <unistd.h>

#define VERSION "0.1"

char date_format[30];
int hour = 24;
int show_date = 1;
int show_seconds = 0;
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


void make_display(char* hour, char* seconds, char* date)
{
	strcpy(hour, " 8:12");
	strcpy(seconds, "39");
	strcpy(date, "01 ZAO 2010");
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
		xd_write(cn, "lcd3", hour_x, hour_y, hour);
		if(show_seconds)
			xd_write(cn, "led3", hour_x+55, hour_y+11, seconds);
		if(show_date)
			xd_write(cn, "led4", 16, hour_y+30, date);
		xd_update(cn);
		usleep(1000000);
	}
}
