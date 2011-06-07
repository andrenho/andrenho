import java.util.LinkedList;
import java.util.Queue;


public class Fila extends Elemento {
	
	protected Fila proxima;
	protected int servidores;
	protected double taxaAtendimento;
	protected Servidor[] servidor;

	public Fila(Fila proxima, int servidores, double taxaAtendimento)
	{
		this.proxima = proxima;
		this.servidores = servidores;
		this.taxaAtendimento = taxaAtendimento;
		this.servidor = new Servidor[servidores];
		for(int i=0; i<servidores; i++)
			this.servidor[i] = new Servidor();
	}

	@Override
	public double proximoEvento(double relogio) {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public void executaProximoEvento() {
		// TODO Auto-generated method stub
		
	}

	public void transfereChamado(Chamado chamado) {
		int nTamanho = Integer.MAX_VALUE;
		Servidor escolhido = null;
		for(Servidor s: servidor)
			if(s.size() < nTamanho)
			{
				nTamanho = s.size();
				escolhido = s;
			}
		assert escolhido != null;
		escolhido.add(chamado);
		// TODO - programa servidor para processar evento
	}

}
