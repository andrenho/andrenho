#include "identifier.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "compiler.h"


void yyerror(char *s);


static Type fct_type;


void declare_var(Type type, YYSTYPE id)
{
	// output code
	output("push $a");

	// create variable
	Variable* v = malloc(sizeof(Variable));
	v->name = id.value;
	v->id = malloc(12);
	sprintf(v->id, "$fp-%d", (context->stack += 4));
	v->type = type;
	v->next = NULL;

	// register variable
	if(context->variables == NULL)
		context->variables = v;
	else
	{
		Variable* vn = context->variables;
		while(vn->next)
			vn = vn->next;
		vn->next = v;
	}

}


void get_var(YYSTYPE *id)
{
	Context* c = context;
	while(c)
	{
		Variable* v = c->variables;
		while(v)
		{
			if(!strcmp(v->name, id->value))
			{
				id->value = v->id;
				id->type = v->type;
				return;
			}
			v = v->next;
		}
		c = c->previous;
	}

	char buf[255];
	sprintf(buf, "Variable %s not found.", id->value);
	yyerror(buf);
	exit(1);
}


void function(Type type, YYSTYPE id)
{
	print("%s:", id.value);
	output("mov $fp, $sp", id.value);
	new_context(FUNCTION, id.value);
	fct_type = type;
	fct_type.type = FUNCTION;
}


Type function_type()
{
	return fct_type;
}


void end_function()
{
	Variable* v = context->variables;
	while(v)
	{
		output("pop");
		v = v->next;
	}
	exit_context();
}
