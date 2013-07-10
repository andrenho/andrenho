#ifndef ARRAY_H
#define ARRAY_H

typedef struct Array {
	int len;
	void** get;
} Array;

void a_init(Array* a);
void a_append(Array* a, void* data);
void a_freedata(Array* a);

#endif
