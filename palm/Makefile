CPP = m68k-palmos-g++
CFLAGS = -O2 -palmos5r4

all: pedidos.prc

pedidos.prc: pedidos pedidos.stamp
	build-prc pedidos.prc "Pedidos" TuHe pedidos *.bin
	# rm -f *.[oa] pedidos *.bin *.stamp

pedidos: main.o form.o principal.o pedido.o itens.o \
	 buscacliente.o
	$(CPP) $(CFLAGS) -o pedidos main.o form.o principal.o pedido.o \
		                    itens.o buscacliente.o

main.o: main.cpp
	$(CPP) $(CFLAGS) -c main.cpp

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

pedidos.stamp: pedidos.rcp pedidos.h
	pilrc pedidos.rcp

clean:
	rm -f *.[oa] pedidos *.bin *.stamp

