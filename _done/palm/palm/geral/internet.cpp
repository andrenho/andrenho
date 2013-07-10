#include "internet.h"
#include "debug.h"

Internet::Internet()
{
	UInt16 ifErrs;
	Err error = SysLibFind("Net.lib", &netNum);

	error = NetLibOpen(netNum, &ifErrs);
	if(!error)
	{
		// no error
	}
	else if(error == netErrAlreadyOpen)
	{
		// no error - already open
	}
	else
		debug("error");
}

bool Internet::abrirConexao(char* endereco, int porta)
{
	// TODO - resolver

	Err err;
	int i;
	NetSocketAddrINType* addrp;
	NetSocketAddrType addr;

	socket = NetLibSocketOpen(netNum, netSocketAddrINET, netSocketTypeStream,
			netSocketProtoIPTCP, -1, &err);

	addrp = (NetSocketAddrINType*)&addr;
	addrp->family = netSocketAddrINET;
	addrp->port = NetHToNS(porta);
	addrp->addr = NetHToNL(NetLibAddrAToIN(netNum, endereco));

	i = NetLibSocketConnect(netNum, socket, &addr, sizeof(addr), -1, &err);

	return (i == 0);
}

char Internet::recebeByte()
{
	char buf;
	Err err;
	int i;

	i = NetLibReceive(netNum, socket, &buf, 1, 0, NULL, 0, 20 * SysTicksPerSecond(), &err);
	if(i == 0)
	{
		debug("conexão encerrada");
		return NULL;
	}
	else if(i == -1)
	{
		debug("erro");
		return NULL;
	}
	return buf;
}

bool Internet::enviaDados(char* dados, int tamanho)
{
	int aEnviar = tamanho;
	Err err;
	
	while(aEnviar > 0)
	{
		int enviado = NetLibSend(netNum, socket, dados, aEnviar, 0, NULL, 0, 20 * SysTicksPerSecond(), &err);
		if(enviado == 0)
		{
			debug("conexão encerrada");
			return false;
		}
		else if(enviado == -1)
		{
			debug("erro");
			return false;
		}
		else
			aEnviar -= enviado;
	}

	return true;
}