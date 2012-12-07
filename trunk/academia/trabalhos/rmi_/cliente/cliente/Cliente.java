package cliente;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.math.BigDecimal;
import interfaces.Servidor;

public class Cliente {

	public static void main(String args[])
	{
		if (System.getSecurityManager() == null) {
			System.setSecurityManager(new SecurityManager());
        	}
		try {
			Registry registry = LocateRegistry.getRegistry(args[0]);
			Servidor servidor = (Servidor)registry.lookup("ExemploRMI");
			Processamento tarefa = new Processamento();
			BigDecimal r = servidor.executaTarefa(tarefa);
			System.out.println(r);
		} catch (Exception e) {
			System.err.println("Exceção:");
			e.printStackTrace();
		}
	}
}
