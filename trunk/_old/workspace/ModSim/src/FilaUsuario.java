import java.util.LinkedList;


public class FilaUsuario extends Fila {

	private int numeroFilas;
	public Fila erroManutencao, erroProjeto;
	
	class FilaHomologacao
	{
		public LinkedList<Chamado> filaChamados = new LinkedList<Chamado>();
		public Servidor servidor = new Servidor();
	}
	public FilaHomologacao filasHomologacao[];
	private double chanceDeErroNaEntrega;
	
	public FilaUsuario(Fila proximaOk, int numeroFilas, double mediaAtendimento, double varianciaAtendimento, double chanceDeErroNaEntrega) {
		super("Homologação", proximaOk, 1, mediaAtendimento, varianciaAtendimento);
		this.numeroFilas = numeroFilas;
		this.filasHomologacao = new FilaHomologacao[this.numeroFilas];
		this.chanceDeErroNaEntrega = chanceDeErroNaEntrega;
		for(int i=0; i<this.numeroFilas; i++)
			this.filasHomologacao[i] = new FilaHomologacao();
	}

	@Override
	public double proximoEvento(double relogio) {
		double t = Double.MAX_VALUE;
		for(FilaHomologacao fh: this.filasHomologacao)
			if(fh.servidor.ocupado())
				if(fh.servidor.fimAtendimento < t)
					t = fh.servidor.fimAtendimento;
		return t;
	}

	@Override
	public void executaProximoEvento(double relogio) 
	{
        double t = Double.MAX_VALUE;
        FilaHomologacao filaHomologacao = null;
        for(FilaHomologacao fh: this.filasHomologacao)
            if(fh.servidor.ocupado())
                if(fh.servidor.fimAtendimento < t)
                {
                    t = fh.servidor.fimAtendimento;
                    filaHomologacao = fh;
                }
        if(filaHomologacao != null) // pelo menos um servidor está trabalhando
        {
            // finaliza atendimento
            Chamado chamado = filaHomologacao.servidor.encerraAtendimento();
            chamado.eventos.add(new Chamado.Evento(relogio, "Atendimento concluído (" + chamado.numero + ") [" + this.nome + "]", Chamado.TipoEvento.ENCERROU_ATENDIMENTO));
            
            // transfere para a próxima fila
            if(proxima != null)
            {
            	if(Math.random() < chanceDeErroNaEntrega)
            	{
            		if(chamado.tipo == Chamado.TipoChamado.PROJETO || chamado.tipo == Chamado.TipoChamado.MELHORIA)
            			erroProjeto.recebeChamado(chamado, relogio);
            		else
            			erroManutencao.recebeChamado(chamado, relogio);
            		filaHomologacao.filaChamados.removeLast();
            	}
            	else
            		proxima.recebeChamado(chamado, relogio);
            }
            else
            {
                // encerra chamado
                chamado.eventos.add(new Chamado.Evento(relogio, "Chamado (" + chamado.numero + ") concluído.", Chamado.TipoEvento.ENCERROU_ATENDIMENTO));
            }
            
            // inicia atendimento do próximo chamado
            if(filaHomologacao.filaChamados.size() > 0)
            {
                Chamado ch = filaHomologacao.filaChamados.removeLast();
                recebeChamado(ch, relogio);
            }
        }
	}

	public void recebeChamado(Chamado chamado, double relogio) {
		int usuario = (int)(Math.random() * this.numeroFilas);
		Servidor s = this.filasHomologacao[usuario].servidor; 
		if(!s.ocupado())
		{
			s.atende(chamado, mediaAtendimento, varianciaAtendimento, relogio);
			chamado.eventos.add(new Chamado.Evento(relogio, "Atendimento iniciado (" + chamado.numero + ") [homologador " + usuario + "]", Chamado.TipoEvento.INICIOU_ATENDIMENTO));
		}
		else
		{
			// nenhum servidor disponível
			chamado.eventos.add(new Chamado.Evento(relogio, "Chamado entrou na fila do usuário " + usuario + " na posição " + (fila.size() + 1) + " (" + chamado.numero + ")", Chamado.TipoEvento.ENTROU_NA_FILA));
			this.filasHomologacao[usuario].filaChamados.addFirst(chamado);
		}
	}

}
