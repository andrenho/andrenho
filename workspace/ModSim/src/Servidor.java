

public class Servidor {
    
    private Chamado processando = null;
    public double fimAtendimento = 0.0;
	
	public boolean ocupado() {
		return processando != null;
	}

	public void atende(Chamado chamado, double taxaAtendimento, double relogio) {
		processando = chamado;
		fimAtendimento = relogio + (Math.random() * taxaAtendimento);
	}

    public Chamado encerraAtendimento()
    {
        Chamado ch = processando;
        fimAtendimento = 0.0;
        processando = null;
        return ch;
    }

}
