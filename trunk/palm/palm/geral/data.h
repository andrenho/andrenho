#ifndef DATA_H
#define DATA_H

#include "palmincludes.h"

class Data
{
public:
	Data();
	Data(const Char* data);
	Data(char dia, char mes, int ano);

	void formatarTexto(Char* data);
	void formatarPalm(DateType* data);
private:
	char dia, mes;
	int ano;
};

#endif
