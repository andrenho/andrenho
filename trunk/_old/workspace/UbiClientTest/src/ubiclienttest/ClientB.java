package ubiclienttest;

import compute.Algoritmo;

public class ClientB extends ClientRepresentation {

	private static final long serialVersionUID = -542035762061457572L;

	protected Algoritmo<String> algoritmo = new AlgoritmoVisitas();
	
	@Override
	public Algoritmo<String> getAlgoritmo()
	{
		return algoritmo;
	}
}
