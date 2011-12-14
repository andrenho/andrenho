#include <stdio.h>
#include <stdlib.h>
#include "text.h"
#include "../uthash/uthash.h"

struct my_labels {
	char name[255];
	long address;
	UT_hash_handle hh;
};
static struct my_labels *labels = NULL;

int main()
{
}
