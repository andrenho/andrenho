all:
	gcc `pkg-config --cflags lua5.1` `freetype-config --cflags` -I/usr/include -c -fPIC wp.c -o wp.o
	gcc -shared wp.o -o wp.so -ljpeg `freetype-config --libs`

clean:
	rm -rf wp.o wp.so
