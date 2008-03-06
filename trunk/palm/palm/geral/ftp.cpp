#include "ftp.h"
#include "debug.h"

bool FTP::conectar(char* servidor, int porta, char* usuario, char* senha)
{
	if(!Internet::abrirConexao(servidor, porta))
		return false;

	if(recebeByte() != '+')
		debug("servidor inválido");

	return true;
}

bool FTP::enviaArquivo(char* nome, void* dados, int lenDados)
{
	return false;
}