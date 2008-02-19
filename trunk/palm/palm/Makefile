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
ERROR_CHECKING = -DERROR_CHECK_LEVEL=ERROR_CHECK_FULL
#ERROR_CHECKING = -DERROR_CHECK_LEVEL=ERROR_CHECK_PARTIAL
CFLAGS = -O2 -palmos5r4 -I. -I$(GERAL_DIR) -I$(PEDIDOS_DIR) $(ERROR_CHECKING)

# 
# Objetos
#
GERAL_O = aplicativo.o preferencias.o \
	  pform.o frmmodal.o buscacliente.o \
	  database.o dbcliente.o dbcidade.o dbpedido.o dbproduto.o \
	  debug.o

PEDIDOS_O = apppedidos.o \
	    frmprincipal.o frmpedido.o frmitens.o frmnovoitem.o

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
apppedidos.o: apppedidos.cpp apppedidos.h
frmprincipal.o: frmprincipal.cpp frmprincipal.h
frmpedido.o: frmpedido.cpp frmpedido.h
frmitens.o: frmitens.cpp frmitens.h
frmnovoitem.o: frmnovoitem.cpp frmnovoitem.h

aplicativo.o: aplicativo.cpp aplicativo.h
preferencias.o: preferencias.cpp preferencias.h
pform.o: pform.cpp pform.h
frmmodal.o: frmmodal.cpp frmmodal.h
buscacliente.o: buscacliente.cpp buscacliente.h
database.o: database.cpp database.h
dbcliente.o: dbcliente.cpp dbcliente.h
dbcidade.o: dbcidade.cpp dbcidade.h
dbpedido.o: dbpedido.cpp dbpedido.h
dbproduto.o: dbproduto.cpp dbproduto.h
debug.o: debug.cpp debug.h

.cpp.o:
	$(CPP) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.[oa] *.bin pedido *.stamp *.h

.PHONY : pedido
