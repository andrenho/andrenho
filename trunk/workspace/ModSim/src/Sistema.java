import jsc.distributions.Uniform;

public class Sistema {
	
	public static Uniform rnd = new Uniform();

	public Fila comite, filaAnalistaManutencao, filaAnalistaProjeto, 
	     filaProgramadorManutencao, filaProgramadorProjeto;
	FilaUsuario filaUsuario;
	Gerador gerador;
	
	Elemento[] filas;
	
	public Sistema(ParametrosSistema ps)
	{
		filaUsuario = new FilaUsuario(null, ps.numeroUsuarios, ps.mediaAtendimentoUsuario, ps.varianciaAtendimentoUsuario, ps.chanceDeErroNaEntrega);
		filaProgramadorManutencao = new Fila("Programador (Manutenção)", filaUsuario, ps.numeroProgramadoresManutencao, ps.mediaAtendimentoProgramadorManutencao, ps.varianciaAtendimentoProgramadorManutencao);
		filaProgramadorProjeto = new Fila("Programador (Projeto)", filaUsuario, ps.numeroProgramadoresProjeto, ps.mediaAtendimentoProgramadorProjeto, ps.varianciaAtendimentoProgramadorProjeto);
		filaAnalistaManutencao = new Fila("Analista (Manutenção)", filaProgramadorManutencao, ps.numeroAnalistasMenutancao, ps.mediaAtendimentoAnalistaManutencao, ps.varianciaAtendimentoAnalistaManutencao);
		filaAnalistaProjeto = new Fila("Analista (Projeto)", filaProgramadorProjeto, ps.numeroAnalistasProjeto, ps.mediaAtendimentoAnalistaProjeto, ps.varianciaAtendimentoAnalistaProjeto);
		comite = new Comite("Comitê", filaAnalistaProjeto);
		
		filaUsuario.erroManutencao = filaProgramadorManutencao;
		filaUsuario.erroProjeto = filaProgramadorProjeto;
		
		gerador = new Gerador(filaAnalistaManutencao, comite);
		
		filas = new Elemento[] { comite, filaUsuario, filaProgramadorManutencao, filaProgramadorProjeto, filaAnalistaManutencao, filaAnalistaProjeto, gerador };
	}
	
	
	public double getTempoMedioAtendimento()
	{
		double t = 0.0;
		for(Chamado ch: gerador.chamados)
			t += ch.getTempoAtendimento();
		return t / gerador.chamados.size();
	}

	
	public double getTempoMedioAtendimento(Chamado.TipoChamado tipo)
	{
		double t = 0.0;
		double i = 0;
		for(Chamado ch: gerador.chamados)
			if(ch.tipo == tipo)
			{
				t += ch.getTempoAtendimento();
				i++;
			}
		return t / i;
	}
	
	
	public double getTempoMedioFila()
	{
		double t = 0.0;
		for(Chamado ch: gerador.chamados)
			t += ch.getTempoFila();
		return t / gerador.chamados.size();
	}

	
	public double getTempoMedioFila(Chamado.TipoChamado tipo) 
	{
		double t = 0.0;
		double i = 0.0;
		for(Chamado ch: gerador.chamados)
			if(ch.tipo == tipo)
			{
				t += ch.getTempoFila();
				i++;
			}
		return t / i;
	}
	
	
	public double getTempoMedioServico()
	{
		double t = 0.0;
		for(Chamado ch: gerador.chamados)
			t += ch.getTempoServico();
		return t / gerador.chamados.size();
	}

	
	public double getTempoMedioServico(Chamado.TipoChamado tipo) 
	{
		double t = 0.0;
		double i = 0.0;
		for(Chamado ch: gerador.chamados)
			if(ch.tipo == tipo)
			{
				t += ch.getTempoServico();
				i++;
			}
		return t / i;
	}
	
	
	private void simula(double horas) {
		double relogio = 0.0;
		
		gerador.geraFila(horas);
		System.out.println("Iniciando simulação.");
		
		while(relogio < horas)
		{
			double proxEvento = Double.MAX_VALUE;
			Elemento proxFilaEvento = null;
			for(Elemento fila: filas)
			{
				double prox = fila.proximoEvento(relogio);
				if(prox != 0.0) // sem evento
					if(prox < proxEvento)
					{
						proxEvento = prox;
						proxFilaEvento = fila;
					}
			}
			if(proxFilaEvento != null)
			{
                relogio = proxEvento;
				proxFilaEvento.executaProximoEvento(relogio);
			}
			else
			    break;
		}
		
		System.out.println("Simulação concluída.");
		
		for(Chamado chamado: gerador.chamados)
		{
		    System.out.println("------------------------------------");
		    System.out.println("CHAMADO " + chamado.numero);
    		for(Chamado.Evento evento: chamado.eventos)
    		    System.out.println(evento.tempo + " - " + evento.descricao);
		}
	}

	public static void main(String[] args) {
		double tempoSimulacao = 5000;
		
		//
		// simulação
		//
		ParametrosSistema ps = new ParametrosSistema();
		Sistema sistema = new Sistema(ps);
		sistema.simula(tempoSimulacao);
		
		//
		// parâmetros de saída
		//
		
		// taxa de utilização, tempo de ocupação
		System.out.println("--------------------------------");
		System.out.println("PARÂMTEROS DE SAÍDA:");
		System.out.println("");
		System.out.println("TAXA DE UTILIZACAO:");
		for(Fila fila: new Fila[] { sistema.filaProgramadorManutencao, sistema.filaProgramadorProjeto, 
				                    sistema.filaAnalistaManutencao, sistema.filaAnalistaProjeto})
		{
			System.out.println(fila.nome + ":");
			int i = 0;
			for(Servidor s: fila.servidor)
				System.out.println("  Servidor " + (i++) + "=> Tx.Utl: " + s.getTaxaUtilizacao(tempoSimulacao) + "   Tempo ocupado: " + s.getTempoOcupado());
		}
		int i=0;
		System.out.println(sistema.filaUsuario.nome + ":");
		for(FilaUsuario.FilaHomologacao fh: sistema.filaUsuario.filasHomologacao)
			System.out.println("  Homolgador " + (i++) + "=> Tx.Utl: " + fh.servidor.getTaxaUtilizacao(tempoSimulacao) + "   Tempo ocupado: " + fh.servidor.getTempoOcupado());
		
		//
		// tempos médios
		//
		System.out.println("");
		System.out.println("TEMPOS MÉDIOS:");
		System.out.println("Tempo médio de atendimento (GERAL): " + sistema.getTempoMedioAtendimento());
		System.out.println("Tempo médio de fila (GERAL): " + sistema.getTempoMedioFila());
		System.out.println("Tempo médio de serviço (GERAL): " + sistema.getTempoMedioServico());
		for(Chamado.TipoChamado tipo: Chamado.TipoChamado.values())
		{
			System.out.println("");
			System.out.println("Tempo médio de atendimento (" + tipo.toString() + "): " + sistema.getTempoMedioAtendimento(tipo));
			System.out.println("Tempo médio de fila (" + tipo.toString() + "): " + sistema.getTempoMedioFila(tipo));
			System.out.println("Tempo médio de serviço (" + tipo.toString() + "): " + sistema.getTempoMedioServico(tipo));
		}
		
		//
		// tamanhos médios de fila
		// 
		System.out.println("");
		System.out.println("TAMANHO MÉDIO DAS FILAS:");
		for(Fila fila: new Fila[] { sistema.filaProgramadorManutencao, sistema.filaProgramadorProjeto, 
									sistema.filaAnalistaManutencao, sistema.filaAnalistaProjeto})
			System.out.println("Tamanho médio (" + fila.nome + "): " + fila.getTamanhoMedioFila(tempoSimulacao));
	}
}
