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

	if(str == NULL)
		return 0;
	if(StrCompare(str, "") == 0)
		return 0;

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

void fmtdbl(double numero, int casas, char* buffer)
{
	int inteiro = (int)numero;
	double decimal = numero - (double)inteiro;
	double sub;
	int mult = 1;
	char b[10];
	int i;
	
	if(casas >= 0)
	{
		for(i=0; i<casas; i++)
			mult *= 10;
		sub = decimal * mult;
	
		StrPrintF(b, "%%d,%%0%dd", casas);
		StrPrintF(buffer, b, inteiro, (int)sub);
	}
	else
	{
		if(decimal == 0)
			StrPrintF(buffer, "%d", inteiro);
		else
		{
			int j;
			
			for(i=0; i<4; i++)
				mult *= 10;
			sub = decimal * mult;
			
			StrPrintF(buffer, "%d,%d", inteiro, (int)sub);
			j = StrLen(buffer);
			for(i=(j-1); i--; i>=0)
				if(buffer[i] == '0')
					buffer[i] = 0;
				else
					break;
		}
	}
}

bool insideRect(int x, int y, int x1, int y1, int x2, int y2)
{
	if(x >= x1 && x <= x2 && y >= y1 && y <= y2)
		return true;
	else
		return false;
}
