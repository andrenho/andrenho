CPP = m68k-palmos-g++
CFLAGS = -g -O2 -palmos5r4

all: pedidos.prc

pedidos.prc: pedidos.stamp pedidos
	build-prc pedidos.prc "Pedidos" TuHe pedidos *.bin
	# rm -f *.[oa] pedidos *.bin *.stamp

pedidos: main.o form.o principal.o pedido.o itens.o \
	 buscacliente.o database.o dbcliente.o
	$(CPP) $(CFLAGS) -o pedidos main.o form.o principal.o pedido.o \
		                    itens.o buscacliente.o database.o  \
				    dbcliente.o

main.o: main.cpp
	$(CPP) $(CFLAGS) -c main.cpp

database.o: database.cpp database.h
	$(CPP) $(CFLAGS) -c database.cpp

dbcliente.o: dbcliente.cpp dbcliente.h
	$(CPP) $(CFLAGS) -c dbcliente.cpp

form.o: form.cpp form.h
	$(CPP) $(CFLAGS) -c form.cpp

principal.o: principal.cpp principal.h
	$(CPP) $(CFLAGS) -c principal.cpp

pedido.o: pedido.cpp pedido.h
	$(CPP) $(CFLAGS) -c pedido.cpp

itens.o: itens.cpp itens.h
	$(CPP) $(CFLAGS) -c itens.cpp

buscacliente.o: buscacliente.cpp buscacliente.h
	$(CPP) $(CFLAGS) -c buscacliente.cpp

pedidos.stamp: pedidos.rcp
	pilrc pedidos.rcp

clean:
	rm -f *.[oa] pedidos *.bin *.stamp

