#include <stdio.h>
#include <stdlib.h>

/* 
 * types
 */
typedef struct {
} Schematic;

/*
 * prototypes
 */
Schematic* parse(FILE* f);
void output(Schematic* sch, FILE* f);

/*
 * code
 */
int main()
{
  Schematic* schem = parse(stdin);
  if(schem)
  {
    output(schem, stdout);
    return EXIT_SUCCESS;
  }
  else
  {
    fprintf(stderr, "Error generating schematic.\n");
    return EXIT_FAILURE;
  }
}


Schematic* parse(FILE* f)
{
  return NULL;
}


void output(Schematic* sch, FILE* f)
{
}
