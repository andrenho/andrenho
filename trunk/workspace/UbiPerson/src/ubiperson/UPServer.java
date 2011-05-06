package ubiperson;

import upserver.UPCommunication;
import upserver.UPServices;

public class UPServer {
	
	public static void main(String[] args) throws Exception
	{
		UPServices services = new UPServices();
		UPCommunication comm = new UPCommunication(services, 8080);
		comm.run();
	}

}
