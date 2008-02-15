# 
# Ferramentas
#
CPP = m68k-palmos-g++

# 
# Diretórios
# 
GERAL_DIR = palm/geral
PEDIDOS_DIR = palm/pedidos
VPATH = $(GERAL_DIR) $(PEDIDOS_DIR)

#
# Flags
#
CFLAGS = -O2 -palmos5r4 -I. -I$(GERAL_DIR) -I$(PEDIDOS_DIR)

# 
# Objetos
#
GERAL_O = events.o \
	  pform.o buscacliente.o \
	  database.o dbcliente.o 

PEDIDOS_O = mainpedidos.o \
	    principal.o pedido.o itens.o

# 
# Regra padrão
#
all: pedidos

#
# Regras executáveis Palm
# 
pedidos: pedidos.prc

pedidos.prc: pedido.stamp pedido
	build-prc pedidos.prc "Pedidos" TuHe pedido *.bin

pedido: $(GERAL_O) $(PEDIDOS_O)
	$(CPP) -o pedido $^

pedido.stamp: pedido.rcp
	pilrc $^

#
# Regras de compilação
# 
mainpedidos.o: mainpedidos.cpp 
principal.o: principal.cpp principal.h
pedido.o: pedido.cpp pedido.h
itens.o: itens.cpp itens.h

events.o: events.cpp events.h
pform.o: pform.cpp pform.h
buscacliente.o: buscacliente.cpp buscacliente.h
database.o: database.cpp database.h
dbcliente.o: dbcliente.cpp dbcliente.h

.cpp.o:
	$(CPP) -c -o $@ $< $(CFLAGS)

clean:
	rm -f *.[oa] *.bin pedido *.stamp *.h

.PHONY : pedido
