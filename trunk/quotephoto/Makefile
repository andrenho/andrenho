#CONVERT=c:\andre\programas\ImageMagick\convert.exe
CONVERT=convert

all: vainwrite.en.jpg vainwrite.pt.jpg house.en.jpg

vainwrite.en.jpg: _vainwrite.jpg
	$(CONVERT) _vainwrite.jpg \
		-stroke black -strokewidth 4 -pointsize 35 -font Kingthings.ttf -annotate +60+90 'How vain it is to sit down to write\nwhen you have not stood up to live.\n-- Thoreau' \
	    -stroke none  -fill white    -pointsize 35 -font Kingthings.ttf -annotate +60+90 'How vain it is to sit down to write\nwhen you have not stood up to live.\n-- Thoreau' \
		vainwrite.en.jpg

vainwrite.pt.jpg: _vainwrite.jpg
	$(CONVERT) _vainwrite.jpg \
		-stroke black -strokewidth 4 -pointsize 35 -font Kingthings.ttf -annotate +60+90 'Quão vão é sentar-se para escrever\nquando você não se levantou para viver.\n-- Thoreau' \
	    -stroke none  -fill white    -pointsize 35 -font Kingthings.ttf -annotate +60+90 'Quão vão é sentar-se para escrever\nquando você não se levantou para viver.\n-- Thoreau' \
		vainwrite.pt.jpg

house.en.jpg: _house.jpg
	$(CONVERT) _house.jpg \
		\( xc:none -stroke black -strokewidth 4  -pointsize 50 -font WC_RoughTrad.ttf -annotate +60+730 'A man builds a fine house;\nand now he has a master, and a task for life:\nhe is to furnish, watch, show it,\nand keep it in repair, the rest of his days.\n-- Thoureau' -blur 0,8 \) \
		\( xc:none -stroke none -fill '#00ff00' -pointsize 50 -font WC_RoughTrad.ttf -annotate +60+730 'A man builds a fine house;\nand now he has a master, and a task for life:\nhe is to furnish, watch, show it,\nand keep it in repair, the rest of his days.\n-- Thoureau' \) \
		_house.jpg -flatten house.en.jpg

#convert dragon.gif -gravity south \
          -stroke '#000C' -strokewidth 2 -annotate 0 'Faerie Dragon' \
          -stroke  none   -fill white    -annotate 0 'Faerie Dragon' \
          anno_outline.jpg


clean:
	rm -f vainwrite.en.jpg vainwrite.pt.jpg
