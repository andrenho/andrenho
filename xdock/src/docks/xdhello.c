#include <xdock.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	XD_Connection *cn = xd_connect(argc, argv, "HELLO");
	if(!cn)
		return 1;

	xd_panel(cn, 4, 4, 88, 88);
	xd_write(cn, "led3", 8, 8, "HELLO WORLD!");
	xd_update(cn);
	for(;;)
	;//	sleep(1);

	return 0;
}
