import java.util.LinkedList;
import java.util.Vector;


public class Gerador extends Elemento {

	private ParametrosSistema ps;
	private Fila proximaManutencao;
	private Fila proximaProjeto;
	private LinkedList<ChamadoTempo> chamadosGerados = new LinkedList<ChamadoTempo>();
	public Vector<Chamado> chamados = new Vector<Chamado>();

	public Gerador(Fila proximaManutencao, Fila proximaProjeto, ParametrosSistema ps)
	{
	    this.nome = "Gerador";
		this.proximaManutencao = proximaManutencao;
		this.proximaProjeto = proximaProjeto;
		this.ps = ps;
	}

	public void geraFila(double maxTempo) {
		geraFila(maxTempo, Chamado.TipoChamado.CORRECAO, ps.taxaChegadaCorrecoes);
		geraFila(maxTempo, Chamado.TipoChamado.ATUALIZACAO, ps.taxaChegadaAtualizacao);
		geraFila(maxTempo, Chamado.TipoChamado.SUPORTE, ps.taxaChegadaSuporte);
		geraFila(maxTempo, Chamado.TipoChamado.MELHORIA, ps.taxaChegadaMelhoria);
		geraFila(maxTempo, Chamado.TipoChamado.PROJETO, ps.taxaChegadaProjeto);
	}

	private void geraFila(double maxTempo, Chamado.TipoChamado tipoChamado,
			double taxaChegada) {
		double t = 0.0;
		while(t < maxTempo)
		{
			t += taxaChegada * Math.random();
			Chamado ch = new Chamado(tipoChamado);
			chamadosGerados.add(new ChamadoTempo(ch, t));
			ch.eventos.add(new Chamado.Evento(t, "Chamado (" + ch.numero + ") inicializado.")); 
			chamados.add(ch);
		}
	}

	@Override
	public double proximoEvento(double relogio) {
		double minTempo = Double.MAX_VALUE;
		for(ChamadoTempo ct: chamadosGerados)
			if(ct.tempo < minTempo && ct.tempo > relogio)
				minTempo = ct.tempo;
		
		return minTempo;
	}

	@Override
	public void executaProximoEvento(double relogio) {
		double minTempo = Double.MAX_VALUE;
		Chamado proxChamado = null;
		for(ChamadoTempo ct: chamadosGerados)
			if(ct.tempo >= relogio && ct.tempo < minTempo)
			{
				minTempo = ct.tempo;
				proxChamado = ct.chamado;
			}
		assert proxChamado != null;
		
		if(proxChamado.tipo == Chamado.TipoChamado.ATUALIZACAO 
		|| proxChamado.tipo == Chamado.TipoChamado.CORRECAO
		|| proxChamado.tipo == Chamado.TipoChamado.SUPORTE)
			proximaManutencao.transfereChamado(proxChamado, relogio);
		else
			proximaProjeto.transfereChamado(proxChamado, relogio);
	}
	
}
