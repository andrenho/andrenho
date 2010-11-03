#include <xdock.h>
#include <stdio.h>
#include <unistd.h>

#define VERSION "0.1"

static void show_help(FILE* f)
{
	fprintf(f,"\
Usage: xdclock [OPTION]...\n
Clock applet to display the date/hour using xdock.\n
\n
All arguments are optional.\n
  -f, --date-format=FORMAT      Use a date format, according to the formats in\n
                                strftime.\n
  -h, --hour=VALUE              Choose between 12-hour or 24-hour clock\n
                                (possible values: 12 or 24).\n
  -n, --no-date                 Don't display the date.\n
  -i, --inexact=LEVEL           Display a inexact clock, where the level of\n
                                inexactitude is between 1 and 3.\n
  -s, --seconds                 Display the seconds in the clock.\n
  -u, --uptime                  Display uptime instead of current time.\n");
}


static void show_version()
{
	printf("xdclock version " VERSION "\n");
	exit(0);
}


void make_display(char* hour, char* seconds, char* date)
{
	strcpy(hour, "12:00");

}


int main(int argc, char* argv[])
{
	XD_Connection *cn = xd_connect(argc, argv, "HELLO");
	if(!cn)
		return 1;


	for(;;)
		usleep(1000000);

	return 0;
}
