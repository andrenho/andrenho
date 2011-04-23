import java.util.Vector;

class Pessoa {

    String nome;
    Vector<Relacionamento> amigos;

    public Pessoa(String nome)
    {
        this.nome = nome;
        amigos = new Vector<Relacionamento>();
    }

    public void novoEvento(Pessoa amigo, double grau)
    {
        for(Relacionamento a: amigos)
            if(a.pessoa == amigo)
            {
                a.grau += grau;
                return;
            }
        amigos.add(new Relacionamento(amigo, grau));
    }
}
