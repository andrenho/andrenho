#include "ftp.h"
#include "debug.h"

bool FTP::conectar(char* servidor, int porta, char* usuario, char* senha)
{
	if(!Internet::abrirConexao(servidor, porta))
		return false;

	if(recebeByte() != '+')
		debug("servidor inválido");

	if(!enviaDados(usuario, StrLen(usuario)))
		debug("dados não puderam ser enviados");
	if(!enviaDados("\n", StrLen("\n")))
		debug("dados não puderam ser enviados");

	if(recebeByte() != '+')
		debug("usuário inválido");

	if(!enviaDados(usuario, StrLen(senha)))
		debug("dados não puderam ser enviados");
	if(!enviaDados("\n", StrLen("\n")))
		debug("dados não puderam ser enviados");

	if(recebeByte() != '+')
		debug("senha inválida");

	return true;
}

bool FTP::enviaArquivo(char* nome, char* dados, int lenDados)
{
	return false;
}