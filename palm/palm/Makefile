# 
# Ferramentas
#
CPP = m68k-palmos-g++
MULTIGEN = m68k-palmos-multigen

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
CFLAGS = -O2 -palmos5r4 -I. -I$(GERAL_DIR) -I$(PEDIDOS_DIR) $(ERROR_CHECKING) # -Wall -Werror 

# 
# Objetos
#
GERAL_O = aplicativo.o preferencias.o \
	  pform.o frmmodal.o buscacliente.o \
	  database.o dbcliente.o dbcidade.o dbpedido.o dbproduto.o \
	  dbpedidoitem.o dbpagto.o dbparcela.o \
	  debug.o util.o data.o lista.o

PEDIDOS_O = apppedidos.o \
	    frmprincipal.o frmpedido.o frmitens.o frmnovoitem.o \
	    frmfinaliza.o frmenvio.o

# 
# Regras padrão
#
all: pedidos

test: pedidos
	pose -psf session.psf -load_apps pedidos.prc -run_app Pedidos -quit_on_exit

doc:
	CppDoc -autorun -autoquit -suppress-frames-links -overwrite -hier -accept3slash geral pedidos doc/index.html

#
# Regras executáveis Palm
# 
pedidos: pedidos.prc

pedidos.prc: pedido.stamp pedido pedidos-sections.ld
	build-prc pedidos.prc "Pedidos" TuHe pedido *.bin pedidos/pedidos.def

pedido: $(GERAL_O) $(PEDIDOS_O) pedidos-sections.ld pedidos-sections.o
	$(CPP) -o pedido $^ pedidos-sections.ld

pedido.stamp: pedido.rcp
	pilrc -q $^

pedidos-sections.o: pedidos-sections.s
	$(CPP) -c pedidos-sections.s -o pedidos-sections.o

pedidos-sections.s pedidos-sections.ld: pedidos/pedidos.def
	$(MULTIGEN) pedidos/pedidos.def

#
# Regras de compilação
# 
apppedidos.o: apppedidos.cpp apppedidos.h
frmprincipal.o: frmprincipal.cpp frmprincipal.h
frmpedido.o: frmpedido.cpp frmpedido.h
frmitens.o: frmitens.cpp frmitens.h
frmnovoitem.o: frmnovoitem.cpp frmnovoitem.h
frmfinaliza.o: frmfinaliza.cpp frmfinaliza.h
frmenvio.o: frmenvio.cpp frmenvio.h

aplicativo.o: aplicativo.cpp aplicativo.h
preferencias.o: preferencias.cpp preferencias.h
pform.o: pform.cpp pform.h
frmmodal.o: frmmodal.cpp frmmodal.h
buscacliente.o: buscacliente.cpp buscacliente.h
database.o: database.cpp database.h
dbcliente.o: dbcliente.cpp dbcliente.h
dbCidade.o: dbcidade.cpp dbcidade.h
dbpedido.o: dbpedido.cpp dbpedido.h
dbpedidoitem.o: dbpedidoitem.cpp dbpedidoitem.h
dbproduto.o: dbproduto.cpp dbproduto.h
dbpagto.o: dbpagto.cpp dbpagto.h
dbparcela.o: dbparcela.cpp dbparcela.h
debug.o: debug.cpp debug.h
util.o: util.cpp util.h
data.o: data.cpp data.h
lista.o: lista.cpp lista.h

.cpp.o:
	$(CPP) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.[oa] *.bin pedido *.stamp *.h

.PHONY : pedido
