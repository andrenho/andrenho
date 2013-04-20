all: main.hex

main.elf: main.c
	avr-gcc -mmcu=attiny2313 -Wall -Os -omain.elf main.c

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex

assembly: main.c
	avr-gcc -S -mmcu=attiny2313 -Wall -Os -omain.s main.c

upload: main.hex
	avrdude -pattiny2313 -cavrisp -b19200 -P/dev/ttyACM0 -U flash:w:main.hex
	# -C C:\temp\arduino-1.0.4\hardware\tools\avr\etc\avrdude.conf

fuse:
	avrdude -pattiny2313 -cstk500v1 -P/dev/ttyACM0 -b19200 -e -Uefuse:w:0xFF:m -Uhfuse:w:0x9F:m -Ulfuse:w:0xE4:m

clean:
	rm -f *.hex *.elf *.s
