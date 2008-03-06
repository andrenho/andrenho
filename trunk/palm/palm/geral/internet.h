#ifndef INTERNET_H
#define INTERNET_H

#include "segment.h"
#include "palmincludes.h"

class Internet
{
public:
	Internet() GERAL;
protected:
	bool abrirConexao(char* endereco, int porta) GERAL;
	char recebeByte();
private:
	UInt16 netNum;
	NetSocketRef socket;
};

#endif
