%{

#define YYDEBUG 1

#include <stdlib.h>
#include "compiler.h"
#include "type.h"
#include "error.h"

int yylex();
void yyerror(char *s);
void unsupported(char const* feature);
extern char yytext[];

//Type type = { OBJECT, _INT, true, NULL, NULL, 0 };

%}

%token IDENTIFIER CONSTANT STRING_LITERAL SIZEOF
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME

%token TYPEDEF EXTERN STATIC AUTO REGISTER
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%union {
	unsigned long value;
	char* name;
}

%type<value> CONSTANT
%type<name> declarator IDENTIFIER

%start translation_unit

%%

primary_expression
	: IDENTIFIER		{ variable($1); }
	| CONSTANT		{ constant($1); }
	| STRING_LITERAL	{ unsupported("string literal"); }
	| '(' expression ')'
	;

postfix_expression
	: primary_expression
	| postfix_expression '[' expression ']'			{ unsupported("array"); }
	| postfix_expression '(' ')'				{ unsupported("function-call"); }
	| postfix_expression '(' argument_expression_list ')'	{ unsupported("function-call (with parameters)"); }
	| postfix_expression '.' IDENTIFIER			{ unsupported("dotted variable"); }
	| postfix_expression PTR_OP IDENTIFIER			{ unsupported("pointer"); }
	| postfix_expression INC_OP				{ unsupported("increment (post)"); }
	| postfix_expression DEC_OP				{ unsupported("decrement (post)"); }
	;

argument_expression_list
	: assignment_expression
	| argument_expression_list ',' assignment_expression
	;

unary_expression
	: postfix_expression
	| INC_OP unary_expression				{ unsupported("increment (pre)"); }
	| DEC_OP unary_expression				{ unsupported("increment (pre)"); }
	| unary_operator cast_expression
	| SIZEOF unary_expression				{ unsupported("sizeof-exp"); }
	| SIZEOF '(' type_name ')'				{ unsupported("sizeof-type"); }
	;

unary_operator
	: '&'	{ unsupported("variable address"); }
	| '*'	{ unsupported("pointer"); }
	| '+'	{ unsupported("unary +"); }
	| '-'	{ unsupported("unary -"); }
	| '~'	{ unsupported("unary ~"); }
	| '!'	{ unsupported("unary !"); }
	;

cast_expression
	: unary_expression
	| '(' type_name ')' cast_expression	{ unsupported("cast"); }
	;

multiplicative_expression
	: cast_expression
	| multiplicative_expression '*' cast_expression	{ unsupported("miltiplication"); }
	| multiplicative_expression '/' cast_expression	{ unsupported("division"); }
	| multiplicative_expression '%' cast_expression	{ unsupported("rest"); }
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression	{ unsupported("sum"); }
	| additive_expression '-' multiplicative_expression	{ unsupported("substraction"); }
	;

shift_expression
	: additive_expression
	| shift_expression LEFT_OP additive_expression	{ unsupported("shift left"); }
	| shift_expression RIGHT_OP additive_expression	{ unsupported("shift right"); }
	;

relational_expression
	: shift_expression
	| relational_expression '<' shift_expression	{ unsupported("less than"); }
	| relational_expression '>' shift_expression	{ unsupported("greater than"); }
	| relational_expression LE_OP shift_expression	{ unsupported("leq than"); }
	| relational_expression GE_OP shift_expression	{ unsupported("geq than"); }
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OP relational_expression	{ unsupported("equals"); }
	| equality_expression NE_OP relational_expression	{ unsupported("not equals"); }
	;

and_expression
	: equality_expression
	| and_expression '&' equality_expression	{ unsupported("and (&)"); }
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression '^' and_expression	{ unsupported("xor (^)"); }
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression '|' exclusive_or_expression	{ unsupported("or (|)"); }
	;

logical_and_expression
	: inclusive_or_expression
	| logical_and_expression AND_OP inclusive_or_expression	{ unsupported("and (&&)"); }
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression OR_OP logical_and_expression	{ unsupported("or (||)"); }
	;

conditional_expression
	: logical_or_expression
	| logical_or_expression '?' expression ':' conditional_expression	{ unsupported("conditional"); }
	;

assignment_expression
	: conditional_expression
	| unary_expression assignment_operator assignment_expression	{ no_dereference(); assignment(); }
	;

assignment_operator
	: '='
	| MUL_ASSIGN	{ unsupported("mul assignment"); }
	| DIV_ASSIGN	{ unsupported("div assignment"); }
	| MOD_ASSIGN	{ unsupported("mod assignment"); }
	| ADD_ASSIGN	{ unsupported("add assignment"); }
	| SUB_ASSIGN	{ unsupported("sub assignment"); }
	| LEFT_ASSIGN	{ unsupported("left assignment"); }
	| RIGHT_ASSIGN	{ unsupported("right assignment"); }
	| AND_ASSIGN	{ unsupported("and assignment"); }
	| XOR_ASSIGN	{ unsupported("xor assignment"); }
	| OR_ASSIGN	{ unsupported("or assignment"); }
	;

expression
	: assignment_expression
	| expression ',' assignment_expression
	;

constant_expression
	: conditional_expression
	;

declaration
	: declaration_specifiers ';'
	| declaration_specifiers init_declarator_list ';'
	;

init_type /* empty */
        : { type_init(); }

declaration_specifiers
	: init_type storage_class_specifier				{ type_end(); }
	| init_type storage_class_specifier declaration_specifiers	{ type_end(); }
	| init_type type_specifier					{ type_end(); }
	| init_type type_specifier declaration_specifiers		{ type_end(); }
	| init_type type_qualifier					{ type_end(); }
	| init_type type_qualifier declaration_specifiers		{ type_end(); }
	;

init_declarator_list
	: init_declarator
	| init_declarator_list ',' init_declarator
	;

init_declarator
	: declarator { declaration($1); }
	| declarator '=' initializer { declaration($1); }
	;

storage_class_specifier
	: TYPEDEF	{ unsupported("typedef"); }
	| EXTERN	{ unsupported("extern"); }
	| STATIC	{ unsupported("static"); }
	| AUTO
	| REGISTER	{ unsupported("register"); }
	;

type_specifier
	: VOID				{ unsupported("void"); }
	| CHAR				{ unsupported("char"); }
	| SHORT				{ unsupported("short"); }
	| INT
	| LONG
	| FLOAT				{ unsupported("float"); }
	| DOUBLE			{ unsupported("double"); }
	| SIGNED			{ unsupported("signed"); }
	| UNSIGNED			{ unsupported("unsigned"); }
	| struct_or_union_specifier	{ unsupported("struct"); }
	| enum_specifier		{ unsupported("enum"); }
	| TYPE_NAME	
	;

struct_or_union_specifier
	: struct_or_union IDENTIFIER '{' struct_declaration_list '}'
	| struct_or_union '{' struct_declaration_list '}'
	| struct_or_union IDENTIFIER
	;

struct_or_union
	: STRUCT
	| UNION
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	| type_qualifier specifier_qualifier_list
	| type_qualifier
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' struct_declarator
	;

struct_declarator
	: declarator
	| ':' constant_expression
	| declarator ':' constant_expression
	;

enum_specifier
	: ENUM '{' enumerator_list '}'
	| ENUM IDENTIFIER '{' enumerator_list '}'
	| ENUM IDENTIFIER
	;

enumerator_list
	: enumerator
	| enumerator_list ',' enumerator
	;

enumerator
	: IDENTIFIER
	| IDENTIFIER '=' constant_expression
	;

type_qualifier
	: CONST		{ unsupported("const"); }
	| VOLATILE	{ unsupported("volatile"); }
	;

declarator
	: pointer direct_declarator
	| direct_declarator
	;

direct_declarator
	: IDENTIFIER
	| '(' declarator ')'
	| direct_declarator '[' constant_expression ']'		{ unsupported("array declaration"); }
	| direct_declarator '[' ']'				{ unsupported("array declaration (empty)"); }
	| direct_declarator '(' parameter_type_list ')'		{ unsupported("function declaration (a)"); }
	| direct_declarator '(' identifier_list ')'		{ unsupported("function declaration (b)"); }
	| direct_declarator '(' ')'
	;

pointer
	: '*'
	| '*' type_qualifier_list
	| '*' pointer
	| '*' type_qualifier_list pointer
	;

type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
	;


parameter_type_list
	: parameter_list
	| parameter_list ',' ELLIPSIS
	;

parameter_list
	: parameter_declaration
	| parameter_list ',' parameter_declaration
	;

parameter_declaration
	: declaration_specifiers declarator
	| declaration_specifiers abstract_declarator
	| declaration_specifiers
	;

identifier_list
	: IDENTIFIER
	| identifier_list ',' IDENTIFIER
	;

type_name
	: specifier_qualifier_list
	| specifier_qualifier_list abstract_declarator
	;

abstract_declarator
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'
	| '[' ']'
	| '[' constant_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' constant_expression ']'
	| '(' ')'
	| '(' parameter_type_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_type_list ')'
	;

initializer
	: assignment_expression
	| '{' initializer_list '}'
	| '{' initializer_list ',' '}'
	;

initializer_list
	: initializer
	| initializer_list ',' initializer
	;

statement
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;

labeled_statement
	: IDENTIFIER ':' statement			{ unsupported("label"); }
	| CASE constant_expression ':' statement	{ unsupported("case label"); }
	| DEFAULT ':' statement				{ unsupported("default label"); }
	;

init_block /* empty */
	: { block_init(); }

compound_statement
	: '{' '}'
	| '{' init_block statement_list '}'			{ block_end(); }
	| '{' init_block declaration_list '}'			{ block_end(); }
	| '{' init_block declaration_list statement_list '}'	{ block_end(); }
	;

declaration_list
	: declaration
	| declaration_list declaration
	;

statement_list
	: statement
	| statement_list statement
	;

expression_statement
	: ';'
	| expression ';'
	;

selection_statement
	: IF '(' expression ')' statement			{ unsupported("if"); }
	| IF '(' expression ')' statement ELSE statement	{ unsupported("if-else"); }
	| SWITCH '(' expression ')' statement			{ unsupported("switch"); }
	;

iteration_statement
	: WHILE '(' expression ')' statement						{ unsupported("while"); }
	| DO statement WHILE '(' expression ')' ';'					{ unsupported("do"); }
	| FOR '(' expression_statement expression_statement ')' statement		{ unsupported("for (a)"); }
	| FOR '(' expression_statement expression_statement expression ')' statement	{ unsupported("for (b)"); }
	;

jump_statement
	: GOTO IDENTIFIER ';'		{ unsupported("goto"); }
	| CONTINUE ';'			{ unsupported("continue"); }
	| BREAK ';'			{ unsupported("break"); }
	| RETURN ';'			{ _return(0); }
	| RETURN expression ';'		{ _return(1); }
	;

translation_unit
	: external_declaration
	| translation_unit external_declaration
	;

external_declaration
	: function_definition
	| declaration
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement		{ unsupported("function definition (a)"); }
	| declaration_specifiers declarator { function_init($2); } compound_statement { function_end($2); }
	| declarator declaration_list compound_statement				{ unsupported("function definition (c)"); }
	| declarator compound_statement							{ unsupported("function definition (d)"); }
	;

%%
#include <stdio.h>

int main()
{
	yydebug = 0;
	initialize();
	yyparse();
	finalize();
	return 0;
}
