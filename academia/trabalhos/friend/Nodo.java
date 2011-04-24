class Nodo {

    Pessoa pessoa;
    Nodo pai;
    int profundidade = 0;
    double custo = 0.0;

    public Nodo(Pessoa pessoa)
    {
        this.pessoa = pessoa;
    }

    public boolean equals (Object n)
    {
        if(!(n instanceof Nodo))
            return false;
        if(this.pessoa == ((Nodo)n).pessoa)
            return true;
        else
            return false;
    }

    public String rota()
    {
        if(pai == null)
            return pessoa.nome;
        return pai.rota() + " - " + pessoa.nome;
    }
}
