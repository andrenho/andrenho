import java.util.LinkedList;
import java.util.Vector;

import jsc.distributions.AbstractDistribution;
import jsc.distributions.Exponential;
import jsc.distributions.Gamma;
import jsc.distributions.Weibull;


public class Gerador extends Elemento {

	private Fila proximaManutencao;
	private Fila proximaProjeto;
	private LinkedList<ChamadoTempo> chamadosGerados = new LinkedList<ChamadoTempo>();
	public Vector<Chamado> chamados = new Vector<Chamado>();

	public Gerador(Fila proximaManutencao, Fila proximaProjeto)
	{
	    this.nome = "Gerador";
		this.proximaManutencao = proximaManutencao;
		this.proximaProjeto = proximaProjeto;
	}

	public void geraFila(double maxTempo) {
		geraFila(maxTempo, Chamado.TipoChamado.CORRECAO, new Weibull(64.125, 0.38301));
		geraFila(maxTempo, Chamado.TipoChamado.ATUALIZACAO, new Weibull(213.23, 0.48126));
		geraFila(maxTempo, Chamado.TipoChamado.SUPORTE, new Gamma(844.751, 0.3692));
		geraFila(maxTempo, Chamado.TipoChamado.MELHORIA, new Weibull(219.76, 0.60717));
		geraFila(maxTempo, Chamado.TipoChamado.PROJETO, new Weibull(684.125, 0.42));
	}

	private void geraFila(double maxTempo, Chamado.TipoChamado tipoChamado, AbstractDistribution dist) {
		double t = 0.0;
		while(t < maxTempo)
		{
			t += dist.inverseCdf(Sistema.rnd.random());
			Chamado ch = new Chamado(tipoChamado);
			chamadosGerados.add(new ChamadoTempo(ch, t));
			ch.eventos.add(new Chamado.Evento(t, "Chamado (" + ch.numero + " - " + ch.tipo.toString() + ") inicializado.", Chamado.TipoEvento.CRIADO)); 
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
			proximaManutencao.recebeChamado(proxChamado, relogio);
		else
			proximaProjeto.recebeChamado(proxChamado, relogio);
	}
	
}
