#include "options.h"

Options opt = {
	.toolkit = NO_VIEW,
	.listen_to = LOCALHOST,
	.debug = 1,
	.dock_color = 0x909090,
};

void opt_parse(int argc, char* argv[])
{
	(void) argc;
	(void) argv;
}
