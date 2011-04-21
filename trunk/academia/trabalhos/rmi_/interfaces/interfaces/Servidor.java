package interfaces;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Servidor extends Remote {
	<T> T executaTarefa(Tarefa<T> t) throws RemoteException;
}
