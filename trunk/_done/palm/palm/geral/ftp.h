#ifndef FTP_H
#define FTP_H

#include "internet.h"

class FTP : public Internet
{
public:
	bool conectar(char* servidor, int porta, char* usuario, char* senha) INTERNET;
	bool enviaArquivo(char* nome, char* dados, int lenDados) INTERNET;
};

#endif