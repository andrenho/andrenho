#include "type.h"

#include <stdlib.h>

#include "error.h"

Type* current_type = NULL;

void type_init()
{
	if(current_type)
	{
		free(current_type);
		current_type = NULL;
	}

	current_type = calloc(1, sizeof(current_type));
	current_type->size = 32;
	current_type->pointer = 0;
}


void type_end()
{
}


void type_size(signed char size)
{
	current_type->size = size;
}


void type_cast(Type* from, Type* to)
{
	if(!from->pointer && !to->pointer)
	{
		if(from->size > to->size)
		{
			warning("type casted to a smaller typer");
			unsupported("cast from a bigger type to a smaller type");
		}
		else if(from->size < to->size)
		{
			unsupported("cast from a smaller type to a bigger type");
		}
	}
	else
	{
		unsupported("cast between pointers");
	}
}
