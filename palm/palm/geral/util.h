#ifndef UTIL_H
#define UTIL_H

#include "palmincludes.h"
#include "segment.h"

Char *StrCopyTest(Char *dst, const Char *src) GERAL;
double strToDouble(CharPtr str) GERAL;
void fmtdbl(double numero, int casas, char* buffer) GERAL;
bool insideRect(int x, int y, int x1, int y1, int x2, int y2);

#endif
