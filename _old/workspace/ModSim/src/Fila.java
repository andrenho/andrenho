import java.util.LinkedList;
import java.util.Vector;


public class Fila extends Elemento {
	
	protected Fila proxima;
	protected int servidores;
	protected double mediaAtendimento, varianciaAtendimento;
	protected Servidor[] servidor;
	protected LinkedList<Chamado> fila = new LinkedList<Chamado>();
	
	class EventoFila
	{
		int tamanho;
		double tempo;
	}
	public Vector<EventoFila> eventosFila = new Vector<Fila.EventoFila>();

	public Fila(String nome, Fila proxima, int servidores, double mediaAtendimento, double varianciaAtendimento)
	{
	    this.nome = nome;
		this.proxima = proxima;
		this.servidores = servidores;
		this.mediaAtendimento = mediaAtendimento;
		this.varianciaAtendimento = varianciaAtendimento;
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
            chamado.eventos.add(new Chamado.Evento(relogio, "Atendimento concluído (" + chamado.numero + ") [" + this.nome + "]", Chamado.TipoEvento.ENCERROU_ATENDIMENTO));
            
            // transfere para a próxima fila
            if(proxima != null && chamado.tipo != Chamado.TipoChamado.SUPORTE)
                proxima.recebeChamado(chamado, relogio);
            else
            {
                // encerra chamado
                chamado.eventos.add(new Chamado.Evento(relogio, "Chamado (" + chamado.numero + ") concluído.", Chamado.TipoEvento.ENCERROU_ATENDIMENTO));
            }
            
            // inicia atendimento do próximo chamado
            if(fila.size() > 0)
            {
                Chamado ch = fila.removeLast();
                recebeChamado(ch, relogio);
            }
        }
	}

	public void recebeChamado(Chamado chamado, double relogio) {
		for(Servidor s: servidor)
			if(!s.ocupado())
			{
				s.atende(chamado, mediaAtendimento, varianciaAtendimento, relogio);
				chamado.eventos.add(new Chamado.Evento(relogio, "Atendimento iniciado (" + chamado.numero + ") [" + this.nome + "]", Chamado.TipoEvento.INICIOU_ATENDIMENTO));
				return;
			}
		
		// nenhum servidor disponível
		chamado.eventos.add(new Chamado.Evento(relogio, "Chamado entrou na fila na posição " + (fila.size() + 1) + " (" + chamado.numero + ") [" + this.nome + "]", Chamado.TipoEvento.ENTROU_NA_FILA));
		fila.addFirst(chamado);
		
		EventoFila ef = new EventoFila();
		ef.tamanho = fila.size();
		ef.tempo = relogio;
		eventosFila.add(ef);
	}
	
	public double getTamanhoMedioFila(double fimSimulacao)
	{
		double tf = 0.0;
		if(eventosFila.size() == 0)
			return 0;
		for(int i=0; i<eventosFila.size(); i++)
		{
			double fim;
			if(i == eventosFila.size() - 1)
				fim = fimSimulacao;
			else
				fim = eventosFila.get(i+1).tempo;
			tf += ((fim - eventosFila.get(i).tempo) * eventosFila.get(i).tamanho);
		}
		return tf / eventosFila.size();
	}

}
