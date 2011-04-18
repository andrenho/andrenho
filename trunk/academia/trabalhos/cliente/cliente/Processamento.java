package cliente;

import java.io.Serializable;
import interfaces.*;

public class Processamento implements Tarefa<String>, Serializable {

	public String executa()
	{
		return "42";
	}

}
