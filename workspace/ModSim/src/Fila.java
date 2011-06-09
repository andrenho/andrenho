import java.util.LinkedList;


public class Fila extends Elemento {
	
	protected Fila proxima;
	protected int servidores;
	protected double taxaAtendimento;
	protected Servidor[] servidor;
	protected LinkedList<Chamado> fila = new LinkedList<Chamado>();

	public Fila(String nome, Fila proxima, int servidores, double taxaAtendimento)
	{
	    this.nome = nome;
		this.proxima = proxima;
		this.servidores = servidores;
		this.taxaAtendimento = taxaAtendimento;
		this.servidor = new Servidor[servidores];
		for(int i=0; i<servidores; i++)
			this.servidor[i] = new Servidor();
	}

	@Override
	public double proximoEvento(double relogio) {
		double t = Double.MAX_VALUE;
		for(Servidor s: servidor)
		    if(s.ocupado())
		        if(s.fimAtendimento < t)
		            t = s.fimAtendimento;
		return t;
	}

	@Override
	public void executaProximoEvento(double relogio) {
        double t = Double.MAX_VALUE;
        Servidor servidorEscolhido = null;
        for(Servidor s: servidor)
            if(s.ocupado())
                if(s.fimAtendimento < t)
                {
                    t = s.fimAtendimento;
                    servidorEscolhido = s;
                }
        if(servidorEscolhido != null) // pelo menos um servidor está trabalhando
        {
            // finaliza atendimento
            Chamado chamado = servidorEscolhido.encerraAtendimento();
            chamado.eventos.add(new Chamado.Evento(relogio, "Atendimento concluído (" + chamado.numero + ") [" + this.nome + "]"));
            
            // transfere para a próxima fila
            if(proxima != null)
                proxima.transfereChamado(chamado, relogio);
            else
            {
                // encerra chamado
                chamado.eventos.add(new Chamado.Evento(relogio, "Chamado (" + chamado.numero + ") concluído."));
            }
            
            // inicia atendimento do próximo chamado
            if(fila.size() > 0)
            {
                Chamado ch = fila.removeLast();
                transfereChamado(ch, relogio);
            }
        }
	}

	public void transfereChamado(Chamado chamado, double relogio) {
		for(Servidor s: servidor)
			if(!s.ocupado())
			{
				s.atende(chamado, taxaAtendimento, relogio);
				chamado.eventos.add(new Chamado.Evento(relogio, "Atendimento iniciado (" + chamado.numero + ") [" + this.nome + "]"));
				return;
			}
		
		// nenhum servidor disponível
		chamado.eventos.add(new Chamado.Evento(relogio, "Chamado entrou na fila na posição " + (fila.size() + 1) + " (" + chamado.numero + ") [" + this.nome + "]"));
		fila.addFirst(chamado);
	}

}
