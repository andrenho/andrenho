import java.util.LinkedList;


public class Fila extends Elemento {
	
	protected Fila proxima;
	protected int servidores;
	protected double taxaAtendimento;
	protected Servidor[] servidor;
	protected LinkedList<Chamado> fila = new LinkedList<Chamado>();

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
		for(Servidor s: servidor)
			if(!s.ocupado())
			{
				s.atende(chamado, taxaAtendimento);
				return;
			}
		
		// nenhum servidor disponível
		fila.add(chamado);
	}

}
