import java.util.*;
import java.io.*;

class Relacoes {

    private static Vector<Pessoa> pessoas = new Vector<Pessoa>();

    public static void main(String args[])
    {
        // verifica argumentos
        if(args.length != 1)
        {
            System.err.println("Uso: java Relacoes nome_pessoa");
            System.err.println("  ou java Relacoes dot");
            return;
        }

        // lê arquivo de entrada
        // - vai alimentar o vetor Pessoa com os relacionamentos
        leArquivoEntrada();

        // monta a árvore
        if(args[0].equals("dot"))
            montaArvoreDot();
        else
            try {
                for(Pessoa p: pessoas)
                    if(!p.nome.equals(args[0]))
                        montaArvore(args[0], p.nome, 10);
            } catch (Exception e) {
                e.printStackTrace();
            }
    }


    private static void montaArvore(String nome) throws Exception
    {
        Pessoa inicio = null;
        for(Pessoa p: pessoas)
            if(p.nome.equals(nome))
                inicio = p;
        if(inicio == null)
            throw new Exception("Pessoa não se encontra na lista.");

        Pessoa fim = BP(inicio, 10);
        System.out.println(fim.nome);
    }

    private static Pessoa BP(Pessoa inicio, Pessoa fim, int m)
    {
        Stack<Nodo> fronteira = new Stack<Nodo>();
        fronteira.add(new Nodo(inicio));
        while(!fronteira.empty())
        {
            if(n.pessoa == pessoa)
                return n;
            if(n.getProfundidade() < m)
                fronteira.add(n.sucessores());
        }
        
        return null;
    }


    private static void leArquivoEntrada()
    {
        Scanner s = null;
        try {
            s = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
            while(s.hasNext())
            {
                String p1 = s.next(), p2 = s.next();
                double grau = Double.parseDouble(s.next());
                novaRelacao(p1, p2, grau);
            }
        }
        catch(Exception e)
        {
            System.out.println("Exceção: ");
            e.printStackTrace();
            return;
        }
        finally
        {
            s.close();
        }
    }

    
    private static void novaRelacao(String p1, String p2, double grau)
    {
        Pessoa pessoa1 = encontraPessoa(p1);
        Pessoa pessoa2 = encontraPessoa(p2);
        pessoa1.novoEvento(pessoa2, grau);
        pessoa2.novoEvento(pessoa1, grau);
    }


    private static Pessoa encontraPessoa(String nome)
    {
        for(Pessoa p: pessoas)
            if(p.nome.equals(nome))
                return p;
        Pessoa p = new Pessoa(nome);
        pessoas.add(p);
        return p;
    }

    private static void montaArvoreDot()
    {
        Vector<Pessoa> visitadas = new Vector<Pessoa>();
        StringBuilder s = new StringBuilder();
        s.append("graph G {\n");
        for(Pessoa pessoa: pessoas)
            s.append("\t" + pessoa.nome + ";\n");
        for(Pessoa pessoa: pessoas)
        {
            for(Relacionamento amigo: pessoa.amigos)
                if(!visitadas.contains(amigo.pessoa))
                    s.append("\t" + pessoa.nome + " -- " + amigo.pessoa.nome + " [ label = \"" + amigo.grau + "\"];\n");
            visitadas.add(pessoa);
        }
                    
        s.append("}");
        System.out.println(s.toString());
    }
}
