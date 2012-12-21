#include "countset.h"

#include <stdlib.h>

CountSet* countset()
{
	CountSet* cs = malloc(sizeof(CountSet));
	cs->st = NULL;
	return cs;
}


void cs_free(CountSet* cs)
{
	CS_Struct *st, *tmp;
	HASH_ITER(hh, cs->st, st, tmp)
	{
		HASH_DEL(cs->st, st);
		free(st);
	}
	free(cs);
}


void cs_add(CountSet* cs, int key)
{
	CS_Struct* st;
	HASH_FIND_INT(cs->st, &key, st);
	if(!st)
	{
		st = malloc(sizeof(CS_Struct));
		st->key = key;
		st->count = 0;
		HASH_ADD_INT(cs->st, key, st);
	}
	else
		++st->count;
}


int cs_highest(CountSet* cs)
{
	CS_Struct *st, *tmp;
	int max = 0, key = CS_NOT_FOUND;
	HASH_ITER(hh, cs->st, st, tmp)
	{
		if(st->count > max)
		{
			max = st->count;
			key = st->key;
		}
	}
	return key;
}
