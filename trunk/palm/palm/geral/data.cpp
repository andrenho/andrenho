#include "data.h"

Data::Data()
{
	DateTimeType dataPl;
	UInt32 segundos = TimGetSeconds();
	TimSecondsToDateTime(segundos, &dataPl);
	this->dia = dataPl.day;
	this->mes = dataPl.month;
	this->ano = dataPl.year;
}

Data::Data(char dia, char mes, int ano)
{
	// TODO checar validade
	this->dia = dia;
	this->mes = mes;
	this->ano = ano;
}

Data::Data(Char* data)
{
	char b[5];
	int i;

	b[0] = data[0];
	b[1] = data[1];
	b[2] = NULL;
	this->dia = StrAToI(b);
	b[0] = data[3];
	b[1] = data[4];
	this->mes = StrAToI(b);
	for(i=0; i<5; i++)
		b[i] = data[6-i];
	this->ano = StrAToI(b);
	// TODO checar validade
}

void Data::formatarTexto(Char* data)
{
	DateTemplateToAscii("^0z/^3z/^4l", this->mes, this->dia, this->ano, data, 11);
}

void Data::formatarPalm(DateType* data)
{
	data->day = this->dia;
	data->month = this->mes;
	data->year = this->ano;
}
