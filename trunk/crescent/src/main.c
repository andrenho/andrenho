#include "gui.h"
#include "glue.h"

int main(int argc, char* argv[])
{
	(void)argc, (void)argv;

	// initialize everything
	if(!gui_init())
		return 1;
	if(!glue_init())
		return 1;

	return 0;
}
