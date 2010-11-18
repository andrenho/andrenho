#include "types.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

void yyerror(char *s);

Type _char =   (Type) { VALUE, _CHAR, true, NULL, NULL, 0 },
     _uchar =  (Type) { VALUE, _CHAR, false, NULL, NULL, 0 },
     _short =  (Type) { VALUE, _SHORT, true, NULL, NULL, 0 },
     _ushort = (Type) { VALUE, _SHORT, false, NULL, NULL, 0 },
     _int =    (Type) { VALUE, _INT, true, NULL, NULL, 0 },
     _uint =   (Type) { VALUE, _INT, false, NULL, NULL, 0 },
     _long =   (Type) { VALUE, _LONG, true, NULL, NULL, 0 },
     _ulong =  (Type) { VALUE, _LONG, false, NULL, NULL, 0 };

void parse_constant(YYSTYPE v)
{
	if(v.value[0] == '\'') // character
		v.type = _uchar;
	else if(strchr(v.value, 'f') || strchr(v.value, 'F') || strchr(v.value, '.')) // float
	{
		yyerror("Floats not yet supported.");
		exit(1);
	}
	else
	{
		long n;
		if(v.value[0] == '0')
		{
			if(tolower(v.value[1]) == 'x') // hex
				n = strtol(v.value, NULL, 16);
			else if(tolower(v.value[strlen(v.value)-1]) == 'b')
			{	
				v.value[strlen(v.value)-1] = '\0';
				n = strtol(v.value, NULL, 2);
			}	
			else
				n = strtol(v.value, NULL, 8);
		}
		else
			n = strtol(v.value, NULL, 10);

		// TODO - look for "U" or "L" on the string

		if(n <= _INT_MAX)
			v.type = _int;
		else if((unsigned)n <= _UINT_MAX)
			v.type = _uint;
		else if(n <= _LONG_MAX)
			v.type = _long;
		else if(n <= _ULONG_MAX)
			v.type = _ulong;
		else
		{
			yyerror("Value too big.");
			exit(1);
		}
	}
}


void clear_type()
{
	type = (Type) { OBJECT, _INT, true, NULL, NULL, 0 };
}


YYSTYPE cast(YYSTYPE val1, YYSTYPE val2)
{
	// return (YYSTYPE) { NULL, { VALUE } };
}


void cast_to(Type from, Type to)
{
	if(from.type == OBJECT && (to.type == VALUE || to.type == FUNCTION))
		output("mov $a, [$a]");
}
