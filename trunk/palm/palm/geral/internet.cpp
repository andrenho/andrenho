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
	NetSocketAddrType addr;
	UInt16 nAddr;
	int i;

	i = NetLibReceive(netNum, socket, &buf, 1, NULL, &addr, &nAddr, -1 /* TODO - timeout */, &err);
	if(i == 0)
		debug("conexão encerrada");
	else if(i == -1)
		debug("erro");
	return buf;
}