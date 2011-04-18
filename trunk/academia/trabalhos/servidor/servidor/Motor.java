package servidor;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import interfaces.*;

public class Motor implements Servidor {

	public <T> T executaTarefa(Tarefa<T> t) {
		return t.executa();
	}

	public static void main(String[] args) {
		if (System.getSecurityManager() == null) {
			System.setSecurityManager(new SecurityManager());
		}
		try {
			Servidor motor = new Motor();
			Servidor stub = (Servidor)UnicastRemoteObject.exportObject(motor, 0);
			Registry registry = LocateRegistry.getRegistry();
			registry.rebind("ExemploRMI", stub);
			System.out.println("Conectado.");
		} catch (Exception e) {
			System.err.println("Desconectado.");
			e.printStackTrace();
		}
	}
}
