require 'set'

def monta_grafo(g)
  arestas = Set.new
  vertices = []
  x = 'a'
  g.each do |linha|
    y = 'a'
    linha.each_char do |n|
      if n == '1'
        if x>y then arestas.add y+x else arestas.add x+y end
      end
      y = y.next
    end
    vertices << x
    x = x.next
  end
  return [vertices, arestas.to_a]
end

def no_com_mais_vertices(g)
  v = g[0].clone
  v.sort! do |a, b|
    na = g[1].select{ |aresta| aresta.include? a }.length
    nb = g[1].select{ |aresta| aresta.include? b }.length
    nb <=> na
  end
  return v
end

def caminha(g)
  g_ = g.clone
  c = [no_com_mais_vertices(g_)[0]]
  while not g_[1].empty?
    v = c.last
    incidentes = []
    no_com_mais_vertices(g_).each do |no|
      incidentes += g_[1].select{ |a| a.include? v and a.include? no }
    end
    a = incidentes[0]
    if a == nil
      puts 'Nao foi possivel encontrar um caminho para este grafo.'
      return nil
    end
    g_[1].delete a
    c << a
    c << (a.delete v)
  end
  return c
end

nos, n_impares = 0, 0
while nos < 2
  print 'Quantos nos tem o grafo? '
  nos = gets.to_i
  puts 'Digite um numero maior que 2.' if nos < 2
end

ult = ('a'.ord + nos - 1).chr
puts "Digite os valores para os nos de 'a' a '#{ult}'."
g = []
print '   '; 'a'.upto(ult) { |c| print c }; puts
'a'.upto(ult) do |c|
  print "#{c}: "
  linha = gets.chomp
  if linha.length != nos or (linha =~ /^[01]+$/) == nil
    puts 'Digite apenas caracteres 0 e 1, de acordo com o numero de nos.'
    redo
  end
  g << linha

  # verifica se é impar
  n_impares += 1 if linha.count('1').odd?
end

possui = ([0,2].include? n_impares)
puts "O grafo #{possui ? '' : 'nao '}possui um caminho eleuriano, pois contem #{n_impares} vertice(s) impar(es)."

if possui
  grafo = monta_grafo(g)
  puts ; puts 'O caminho percorrido e:'
  c = caminha(grafo)
  p c if c
end
