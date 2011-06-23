import java.util.Vector;

public class Chamado {
	
	public enum TipoChamado { CORRECAO, SUPORTE, ATUALIZACAO, MELHORIA, PROJETO }
	
	public enum TipoEvento { CRIADO, ENTROU_NA_FILA, INICIOU_ATENDIMENTO, ENCERROU_ATENDIMENTO };

	public final TipoChamado tipo;
    public int numero;
	public static int numeroGeral = 0;
	public Vector<Evento> eventos = new Vector<Evento>();
	
	public static class Evento {
	    double tempo;
	    String descricao;
	    TipoEvento tipoEvento;
	    public Evento(double tempo, String descricao, TipoEvento tipoEvento) {
	        this.tempo = tempo;
	        this.descricao = descricao;
	        this.tipoEvento = tipoEvento;
	        //System.out.println(descricao);
	    }
	}

	public Chamado(TipoChamado tipo)
	{
		this.tipo = tipo;
		this.numero = ++Chamado.numeroGeral;
	}
	
	public double getTempoAtendimento()
	{
		double t = 0.0;
		for(int i=0; i<this.eventos.size(); i++)
			if(eventos.get(i).tipoEvento == TipoEvento.INICIOU_ATENDIMENTO && i+1 < eventos.size())
				t += (eventos.get(i+1).tempo - eventos.get(i).tempo);
		return t;
	}

	public double getTempoFila()
	{
		double t = 0.0;
		for(int i=0; i<this.eventos.size(); i++)
			if(eventos.get(i).tipoEvento == TipoEvento.ENTROU_NA_FILA && i+1 < eventos.size())
				t += (eventos.get(i+1).tempo - eventos.get(i).tempo);
		return t;
	}
	
	public double getTempoServico()
	{
		return getTempoAtendimento() + getTempoFila();
	}
}
