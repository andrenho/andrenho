#ifndef UTIL_H
#define UTIL_H

#include "palmincludes.h"
#include "segment.h"

Char *StrCopyTest(Char *dst, const Char *src) GERAL;
double strToDouble(CharPtr str) GERAL;
void fmtdbl(double numero, int casas, char* buffer) GERAL;

#endif
