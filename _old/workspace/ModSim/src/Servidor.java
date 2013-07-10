import java.util.Vector;

import jsc.distributions.Normal;



public class Servidor {
    
    private Chamado processando = null;
    public double fimAtendimento = 0.0;
    
    public Vector<Atendimento> atendimentos = new Vector<Atendimento>();
	
	public boolean ocupado() {
		return processando != null;
	}

	public void atende(Chamado chamado, double mediaAtendimento, double varianciaAtendimento, double relogio) {
		processando = chamado;
		fimAtendimento = relogio + (new Normal(mediaAtendimento, varianciaAtendimento)).inverseCdf(Sistema.rnd.random());

		Atendimento a = new Atendimento();
		a.inicio = relogio;
		a.fim = fimAtendimento;
		atendimentos.add(a);
	}

    public Chamado encerraAtendimento()
    {
        Chamado ch = processando;
        fimAtendimento = 0.0;
        processando = null;
        return ch;
    }
    
    public double getTaxaUtilizacao(double tempoSimulacao)
    {
    	double livre = 0.0, ocupado = 0.0;
    	if(atendimentos.size() == 0)
    		return 0;
    	else
    	{
    		double ult_liberacao = 0.0;
    		for(Atendimento a: atendimentos)
    		{
    			livre += (a.inicio - ult_liberacao);
    			ocupado += (a.fim - a.inicio);
    		}
    		livre += tempoSimulacao - atendimentos.lastElement().fim;
    		return ocupado / tempoSimulacao;
    	}
    }
    
    public double getTempoOcupado()
    {
    	double s = 0.0;
    	for(Atendimento a: atendimentos)
    		s += (a.fim - a.inicio);
    	return s;
    }

}
