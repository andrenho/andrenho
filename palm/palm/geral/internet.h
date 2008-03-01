#ifndef INTERNET_H
#define INTERNET_H

#include "segment.h"
#include "palmincludes.h"

class Internet
{
public:
	Internet() GERAL;
	bool abrirConexao();
private:
	UInt16 netNum;
	NetSocketRef socket;
};

#endif
