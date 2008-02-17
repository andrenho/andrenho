# 
# Ferramentas
#
CPP = m68k-palmos-g++

# 
# Diretórios
# 
GERAL_DIR = geral
PEDIDOS_DIR = pedidos
VPATH = $(GERAL_DIR) $(PEDIDOS_DIR)

#
# Flags
#
CFLAGS = -O2 -palmos5r4 -I. -I$(GERAL_DIR) -I$(PEDIDOS_DIR)

# 
# Objetos
#
GERAL_O = main.o \
	  pform.o frmmodal.o buscacliente.o frmcidades.o \
	  database.o dbcliente.o 

PEDIDOS_O = mainpedidos.o \
	    frmprincipal.o frmpedido.o frmitens.o

# 
# Regras padrão
#
all: pedidos

test: pedidos
	pose -psf session.psf -load_apps pedidos.prc -run_app Pedidos -quit_on_exit

#
# Regras executáveis Palm
# 
pedidos: pedidos.prc

pedidos.prc: pedido.stamp pedido
	build-prc pedidos.prc "Pedidos" TuHe pedido *.bin

pedido: $(GERAL_O) $(PEDIDOS_O)
	$(CPP) -o pedido $^

pedido.stamp: pedido.rcp
	pilrc -q $^

#
# Regras de compilação
# 
mainpedidos.o: mainpedidos.cpp 
frmprincipal.o: frmprincipal.cpp frmprincipal.h
frmpedido.o: frmpedido.cpp frmpedido.h
frmitens.o: frmitens.cpp frmitens.h

main.o: main.cpp main.h
pform.o: pform.cpp pform.h
frmmodal.o: frmmodal.cpp frmmodal.h
buscacliente.o: buscacliente.cpp buscacliente.h
frmcidades.o: frmcidades.cpp frmcidades.h
database.o: database.cpp database.h
dbcliente.o: dbcliente.cpp dbcliente.h

.cpp.o:
	$(CPP) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.[oa] *.bin pedido *.stamp *.h

.PHONY : pedido
