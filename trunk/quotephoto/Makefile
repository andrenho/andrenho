CONVERT=c:\andre\programas\ImageMagick\convert.exe

all: vainwrite.en.jpg vainwrite.pt.jpg

vainwrite.en.jpg: _vainwrite.jpg
	$(CONVERT) _vainwrite.jpg \
		-stroke black -strokewidth 4 -pointsize 35 -font Kingthings.ttf -annotate +60+90 'How vain it is to sit down to write\nwhen you have not stood up to live.\n-- Thoreau' \
	    -stroke none  -fill white    -pointsize 35 -font Kingthings.ttf -annotate +60+90 'How vain it is to sit down to write\nwhen you have not stood up to live.\n-- Thoreau' \
		vainwrite.en.jpg

vainwrite.pt.jpg: _vainwrite.jpg
	$(CONVERT) _vainwrite.jpg \
		-stroke black -strokewidth 4 -pointsize 35 -font Kingthings.ttf -annotate +60+90 'Quão vão é sentar-se para escrever\nquando não se levantou para viver.\n-- Thoreau' \
	    -stroke none  -fill white    -pointsize 35 -font Kingthings.ttf -annotate +60+90 'Quão vão é sentar-se para escrever\nquando não se levantou para viver.\n-- Thoreau' \
		vainwrite.pt.jpg

#convert dragon.gif -gravity south \
          -stroke '#000C' -strokewidth 2 -annotate 0 'Faerie Dragon' \
          -stroke  none   -fill white    -annotate 0 'Faerie Dragon' \
          anno_outline.jpg


clean:
	rm vainwrite.en.jpg vainwrite.pt.jpg
