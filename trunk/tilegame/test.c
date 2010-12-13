#include "tilegame.h"

#include <stdlib.h>

int main(int argc, char* argv[])
{
	char* err;
	TileGame* tg = TG_Init("./terminal.tg", &err);
	if(!tg)
	{
		fprintf(stderr, "%s\n", err);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
