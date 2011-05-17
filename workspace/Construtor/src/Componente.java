import java.awt.Color;

public class Componente {
	
	public TipoComponente tipo;
	public String nome;
	public char codigo;
	public Color cor;

	protected Componente(TipoComponente tipo, String nome, char codigo, Color cor)
	{
		this.tipo = tipo;
		this.nome = nome;
		this.codigo = codigo;
		this.cor = cor;
	}
	
	public static Componente[] lista = {
		new Componente(TipoComponente.SOLIDO, "Terra", 'T', new Color(128, 64, 0)),
		new Componente(TipoComponente.OBJETO, "Início da Fase", 'i', Color.blue), 
	};
	
}
