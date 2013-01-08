#include "array.h"

#include <stdlib.h>
#include <string.h>

void a_init(Array* a)
{
	memset(a, 0, sizeof(Array));
}


void a_append(Array* a, void* data)
{
	a->get = realloc(a->get, sizeof(Array*) * a->len+1);
	a->get[a->len] = data;
	a->len++;
}


void a_freedata(Array* a)
{
	for(int i=0; i<a->len; i++)
		free(a->get[i]);
}
