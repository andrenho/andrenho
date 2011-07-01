import java.util.Vector;
import jsc.distributions.Normal;


public class Comite extends Fila {

	class FilaComite
	{
		public Chamado chamado;
		public double tempo;
		public FilaComite(Chamado chamado, double tempo) {
			this.chamado = chamado;
			this.tempo = tempo;
		}
	}
	protected Vector<FilaComite> fila = new Vector<FilaComite>();
	
	public Comite(String nome, Fila filaProjeto)
	{
		super(nome, filaProjeto, 0, 0, 0);
	}
	
	@Override
	public void executaProximoEvento(double relogio) {
		double t = Double.MAX_VALUE;
		FilaComite filaComite = null;
		for(FilaComite fc: this.fila)
			if(fc.tempo < t)
			{
				t = fc.tempo;
				filaComite = fc;
			}
		
		if(filaComite != null)
		{
			filaComite.chamado.eventos.add(new Chamado.Evento(relogio, "Chamado redirecionado (" + filaComite.chamado.numero + ") [" + this.nome + "]", Chamado.TipoEvento.ENCERROU_ATENDIMENTO));
			this.proxima.recebeChamado(filaComite.chamado, relogio);
			fila.remove(filaComite);
		}
	}

	@Override
	public double proximoEvento(double relogio) 
	{
		double t = Double.MAX_VALUE;
		for(FilaComite fc: this.fila)
			if(fc.tempo < t)
	            t = fc.tempo;
		return t;
	}

	@Override
	public void recebeChamado(Chamado chamado, double relogio) {
		// double tempo = relogio + Math.random();
	    double tempo = relogio + (new Normal(100, 1).inverseCdf(Sistema.rnd.random()));
		chamado.eventos.add(new Chamado.Evento(relogio, "Chamado entrou no comitê. Previsão: " + tempo + " (" + chamado.numero + ") [" + this.nome + "]", Chamado.TipoEvento.ENTROU_NA_FILA));
		fila.add(new FilaComite(chamado, tempo));
	}
	
}
