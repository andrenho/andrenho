class Gerador {

    public static void main(String args[])
    {
        // Sem parâmetros
        if(args.length == 0)
        {
            System.out.println("Uso: java Gerador n_eventos nomes...");
            return;
        }

        // Número de events
        int n_evt = Integer.parseInt(args[0]);

        // Nomes
        int n_pessoas = args.length-1;
        if(n_pessoas < 2)
        {
            System.out.println("Devem haver pelo menos duas pessoas.");
            return;
        }
        String nomes[] = new String[n_pessoas];
        System.arraycopy(args, 1, nomes, 0, n_pessoas);

        // Gera os events
        for(int i=0; i<n_evt; i++)
        {
            int p1 = (int)(Math.random() * n_pessoas);
            int p2;
            do
                p2 = (int)(Math.random() * n_pessoas);
            while(p1 == p2);
            System.out.print(nomes[p1] + " ");
            System.out.print(nomes[p2] + " ");
            System.out.println(Math.random());
        }
    }

}
