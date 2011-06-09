
public class FilaUsuario extends Fila {

	public Fila erroManutencao, erroProjeto;
	
	public FilaUsuario(Fila proximaOk, int numeroFilas, double taxaAtendimento) {
		super("Homologação", proximaOk, 1, taxaAtendimento);
	}

}
