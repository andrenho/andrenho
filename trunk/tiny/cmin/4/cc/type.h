#ifndef TYPE_H
#define TYPE_H


struct Type {
	signed char size;
	int pointer;
};
extern struct Type* current_type;


void type_init();
void type_end();
void type_size(signed char size);

void type_cast(struct Type* from, struct Type* to);

#endif
