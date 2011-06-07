public class Chamado {
	
	public enum TipoChamado { CORRECAO, SUPORTE, ATUALIZACAO, MELHORIA, PROJETO }

	public final TipoChamado tipo;

	public Chamado(TipoChamado tipo)
	{
		this.tipo = tipo;
	}
}
