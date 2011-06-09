
public class Sistema {

	Fila filaAnalistaManutencao, filaAnalistaProjeto, 
	     filaProgramadorManutencao, filaProgramadorProjeto;
	FilaUsuario filaUsuario;
	Gerador gerador;
	
	Elemento[] filas;
	
	public Sistema(ParametrosSistema ps)
	{
		filaUsuario = new FilaUsuario(null, ps.numeroUsuarios, ps.taxaAtendimentoUsuario);
		filaProgramadorManutencao = new Fila("Programador (Manutenção)", filaUsuario, ps.numeroProgramadoresManutencao, ps.taxaAtendimentoProgramadorManutencao);
		filaProgramadorProjeto = new Fila("Programador (Projeto)", filaUsuario, ps.numeroProgramadoresProjeto, ps.taxaAtendimentoProgramadorProjeto);
		filaAnalistaManutencao = new Fila("Analista (Manutenção)", filaProgramadorManutencao, ps.numeroAnalistasMenutancao, ps.taxaAtendimentoAnalistaManutencao);
		filaAnalistaProjeto = new Fila("Analista (Projeto)", filaProgramadorProjeto, ps.numeroAnalistasProjeto, ps.taxaAtendimentoAnalistaProjeto);
		
		filaUsuario.erroManutencao = filaProgramadorManutencao;
		filaUsuario.erroProjeto = filaProgramadorProjeto;
		
		gerador = new Gerador(filaAnalistaManutencao, filaAnalistaProjeto, ps);
		
		filas = new Elemento[] { filaUsuario, filaProgramadorManutencao, filaProgramadorProjeto, filaAnalistaManutencao, filaAnalistaProjeto, gerador };
	}
	
	private void simula(int dias) {
		double relogio = 0.0;
		
		gerador.geraFila(dias);
		System.out.println("Iniciando simulação.");
		
		while(relogio < dias)
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
		ParametrosSistema ps = new ParametrosSistema();
		Sistema sistema = new Sistema(ps);
		sistema.simula(10);
	}
}
