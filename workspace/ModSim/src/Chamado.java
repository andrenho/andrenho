import java.util.Vector;

public class Chamado {
	
	public enum TipoChamado { CORRECAO, SUPORTE, ATUALIZACAO, MELHORIA, PROJETO }

	public final TipoChamado tipo;
    public int numero;
	public static int numeroGeral = 0;
	public Vector<Evento> eventos = new Vector<Evento>();
	
	public static class Evento {
	    double tempo;
	    String descricao;
	    public Evento(double tempo, String descricao) {
	        this.tempo = tempo;
	        this.descricao = descricao;
	        //System.out.println(descricao);
	    }
	}

	public Chamado(TipoChamado tipo)
	{
		this.tipo = tipo;
		this.numero = ++Chamado.numeroGeral;
	}
}
