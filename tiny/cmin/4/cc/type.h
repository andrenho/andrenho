#ifndef TYPE_H
#define TYPE_H


typedef struct {
	signed char size;
	int pointer;
} Type;
extern Type* current_type;


void type_init();
void type_end();
void type_size(signed char size);

void type_cast(Type* from, Type* to);

#endif
