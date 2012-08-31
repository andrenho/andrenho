#ifndef OUTPUT_H
#define OUTPUT_H

/* This overly complicated way of output data exists because we need to be
 * able to rollback the printing sometimes. */
int output(char* fmt, ...);

#endif
