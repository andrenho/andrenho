#ifndef DATA_H
#define DATA_H

#include "palmincludes.h"
#include "segment.h"

class Data
{
public:
	Data() GERAL;
	Data(const Char* data) GERAL;
	Data(char dia, char mes, int ano) GERAL;

	void ajusta(char dia, char mes, int ano) GERAL;
	void formatarTexto(Char* data) GERAL;
	void formatarPalm(DateType* data) GERAL;
//private:
	char dia, mes;
	int ano;
};

#endif
