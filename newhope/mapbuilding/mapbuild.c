// gcc -o mapbuild mapbuild.c -g `sdl-config --libs --cflags` && ./mapbuild

#include <stdlib.h>

int main(int argc, char** argv)
{
	if(argc != 3)
		abort();
	int w = argv[1];
	int h = argv[2];

	return 0;
}
