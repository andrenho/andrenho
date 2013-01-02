#include "mapbuild.h"

#include <stdlib.h>
#include <string.h>

Map* map_init(MapParameters map_pars)
{
	Map* map = malloc(sizeof(Map));
	MapParameters* pars = malloc(sizeof(MapParameters));
	memcpy(pars, &map_pars, sizeof(MapParameters));
	map->parameters = pars;

	return map;
}

void map_free(Map* map)
{
	free(map->parameters);
	free(map);
}
