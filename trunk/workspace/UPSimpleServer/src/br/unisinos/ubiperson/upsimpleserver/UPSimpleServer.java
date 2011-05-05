package br.unisinos.ubiperson.upsimpleserver;

import java.io.IOException;

public class UPSimpleServer {
	
	public static void main(String[] args) throws Exception
	{
		// inicializa os serviços
		UPServices services = new UPServices();
		UPAuthentication auth = new UPAuthentication();
		UPCommunication comm = new UPCommunication(auth, services);
		
		// inicializa o servidor
		comm.run();
	}

}
