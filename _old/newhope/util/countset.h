#ifndef COUNTSET_H
#define COUNTSET_H

#include "util/uthash.h"
#include <limits.h>

#define CS_NOT_FOUND INT_MIN

typedef struct CS_Struct {
	int key;
	int count;
	UT_hash_handle hh;
} CS_Struct;

typedef struct CountSet {
	CS_Struct* st;
} CountSet;

CountSet* countset();
void cs_free(CountSet* cs);

void cs_add(CountSet* cs, int key);
int cs_highest(CountSet* cs);

#endif
