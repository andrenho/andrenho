package ubiclienttest;

import compute.Algoritmo;

public class ClientA extends ClientRepresentation {

	private static final long serialVersionUID = -1602822581343273988L;
	protected Algoritmo<String> algoritmo = new AlgoritmoTempo();
	
	@Override
	public Algoritmo<String> getAlgoritmo()
	{
		return algoritmo;
	}

}
