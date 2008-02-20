#include "util.h"

Char *StrCopyTest(Char *dst, const Char *src)
{
	if(src == NULL)
		StrCopy(dst, "");
	else
	{
		if(StrCompare(src, "") == 0)
			StrCopy(dst, "");
		else
			StrCopy(dst, src);
	}
	return dst;
}

double strToDouble(Char* str)
{ 
	int pos_virgula = -1;
	int i;
	double num;
	double base = 0.1;

	for(i=0; i<StrLen(str); i++)
		if(str[i] == '.' || str[i] == ',')
			pos_virgula = i;
	num = StrAToI(str);
	if(pos_virgula != -1)
		for(i=pos_virgula+1; i<StrLen(str); i++)
		{
			num += (str[i] - '0') * base;
			base /= 10;
		}


        return num;
}
