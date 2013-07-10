#ifndef INTERNET_H
#define INTERNET_H

#include "segment.h"
#include "palmincludes.h"

class Internet
{
public:
	Internet() INTERNET;
protected:
	bool abrirConexao(char* endereco, int porta) INTERNET;
	char recebeByte() INTERNET;
	bool enviaDados(char* dados, int tamanho) INTERNET;
private:
	UInt16 netNum;
	NetSocketRef socket;
};

#endif
