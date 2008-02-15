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
CFLAGS = -O2 -palmos5r4 -I$(GERAL_DIR) -I$(PEDIDOS_DIR)

# 
# Objetos
#
GERAL_O = events.o \
	  pform.o buscacliente.o \
	  database.o dbcliente.o 

PEDIDOS_O = main.o \
	    principal.o pedido.o itens.o

# 
# Executáveis
#
PEDIDOS_PRC = pedidos.prc
EXECUTAVEIS = $(PEDIDOS_PRC)

# 
# Compilation rules
#

main.o: main.cpp 
principal.o: principal.cpp principal.h
pedido.o: pedido.cpp pedido.h
itens.o: itens.cpp itens.h

events.o: events.cpp events.h
pform.o: pform.cpp pform.h
buscacliente.o: buscacliente.cpp buscacliente.h
database.o: database.cpp database.h
dbcliente.o: dbcliente.cpp dbcliente.h

#
# Rules
# 
all: $(EXECUTAVEIS)

.cpp.o:
	$(CPP) -c -o $@ $< $(CFLAGS)

pedidos.bin: $(GERAL_O) $(PEDIDOS_O)
	$(CPP) -o pedidos.bin $^

pedidos.stamp: pedidos.rcp
	pilrc $^

pedidos.prc: pedidos.stamp pedidos.bin
	build-prc pedidos.prc "Pedidos" TuHe pedidos.bin *.bin

clean:
	rm -f *.[oa] *.obj *.bin *.stamp
