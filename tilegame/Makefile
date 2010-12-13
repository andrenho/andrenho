EXT=dll
SDL=`sdl-config --cflags --libs`

all: test.c terminal.tg libtilegame.$(EXT)
	gcc -o test -g -Wall $(SDL) test.c -L. -ltilegame

libtilegame.$(EXT): tilegame.c
	gcc -shared -g -Wall $(SDL) -o tilegame.$(EXT) tilegame.c

terminal.tg: terminal/index.rc terminal/terminal.rc terminal/terminal.png
	cd terminal && \
	tar zcf terminal.tar.gz *.png *.rc && \
	cd .. && \
	mv terminal/terminal.tar.gz terminal.tg

clean:
	rm -rf libtilegame.$(EXT) terminal.tg test test.exe 
