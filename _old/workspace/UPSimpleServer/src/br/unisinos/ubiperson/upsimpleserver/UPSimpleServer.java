package br.unisinos.ubiperson.upsimpleserver;

public class UPSimpleServer {
	
	public static void main(String[] args) throws Exception
	{
		// inicializa os servi�os
		UPServices services = new UPServices();
		UPAuthentication auth = new UPAuthentication();
		
		// inicializa o servidor
		UPCommunication comm = new UPCommunication(auth, services);
		comm.run();
	}

}
