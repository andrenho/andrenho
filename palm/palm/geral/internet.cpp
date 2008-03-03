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

bool Internet::abrirConexao()
{
	Err err;
	int i;
	NetSocketAddrType addr;
	NetSocketAddrINType* addrp;

	socket = NetLibSocketOpen(netNum, netSocketAddrINET, netSocketTypeStream,
			netSocketProtoIPTCP, -1, &err);

	addrp = (NetSocketAddrINType*)&addr;
	addrp->family = netSocketAddrINET;
	addrp->port = NetHToNS(3389);
	addrp->addr = NetHToNL(NetLibAddrAToIN(netNum, "192.168.100.39"));

	i = NetLibSocketConnect(netNum, socket, &addr, sizeof(addr), -1, &err);

	debug(i);
	return true;
}
