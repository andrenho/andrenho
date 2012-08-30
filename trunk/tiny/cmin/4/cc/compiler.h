#ifndef COMPILER_H
#define COMPILER_H

// Initialize everything
void initialize();
void finalize();

// Function declarations
void function_init(char* name);
void function_end(char* name);

// Block declaration
void block_init();
void block_end();

// Variable declarations
void declaration();

// Data
void constant(unsigned long d);

// Commands
void _return(int has_expression);

#endif
