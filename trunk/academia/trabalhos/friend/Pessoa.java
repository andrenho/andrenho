import java.util.Vector;

class Pessoa {

    String nome;
    Vector<Relacionamento> amigos;
    Vector<Double> graus_eventos;

    public Pessoa(String nome)
    {
        this.nome = nome;
        amigos = new Vector<Relacionamento>();
        graus_eventos = new Vector<Double>();
    }

    public void novoEvento(Pessoa amigo, double grau)
    {
        for(Relacionamento a: amigos)
            if(a.pessoa == amigo)
            {
                /*
                graus_eventos.add(grau);
                a.grau = 0.0;
                for(double evt: graus_eventos)
                    a.grau += evt;
                a.grau /= graus_eventos.size();
                */
                a.grau += grau;
                return;
            }
        amigos.add(new Relacionamento(amigo, grau));
    }
}
