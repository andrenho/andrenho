#include "level.h"

int main()
{
	Level* level = level_load(0);


	level_free(&level);
	return 0;
}
