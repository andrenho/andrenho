
public class TipoComponente {

	public String nome;

	public TipoComponente(String name)
	{
		this.nome = name;
	}
	
	public static final TipoComponente SOLIDO = new TipoComponente("Sólidos"),
	                                   OBJETO = new TipoComponente("Objeto");
	public static final TipoComponente[] lista = { SOLIDO, OBJETO };
}
