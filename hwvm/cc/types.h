#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

typedef struct Type {
	enum { VALUE, OBJECT, ARRAY, POINTER, FUNCTION, STRUCTURE, _UNION } type;

	// basic types
	enum { _VOID, _CHAR=1, _SHORT=2, _INT=4, _LONG=8, _FLOAT, _DOUBLE } basic_type;
	bool _signed;

	// structs and unions
	struct Type* fields;
	struct Type* next;

	// pointers and arrays
	int references;
} Type;

struct YYSTYPE {
	char* value;
	Type type;
};
#define YYSTYPE struct YYSTYPE

void parse_constant(YYSTYPE type);
YYSTYPE cast(YYSTYPE val1, YYSTYPE val2);

#define _CHAR_MAX  	0x7f
#define _UCHAR_MAX	0xff
#define _SHORT_MAX  	0x7fff
#define _USHORT_MAX	0xffff
#define _INT_MAX    	0x7fffffff
#define _UINT_MAX   	0xffffffff
#define _LONG_MAX   	0x7fffffffffffffff
#define _ULONG_MAX  	0xffffffffffffffff

#endif
