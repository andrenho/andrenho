all: main.hex

main.elf: main.c
	avr-gcc -mmcu=atmega328p -Wall -Os -omain.elf main.c

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex

assembly: main.c
	avr-gcc -S -mmcu=atmega328p -Wall -Os -omain.s main.c

upload: main.hex
	avrdude -patmega328p -carduino -b115200 -PCOM3 -U flash:w:main.hex -C C:\temp\arduino-1.0.4\hardware\tools\avr\etc\avrdude.conf

clean:
	rm *.hex *.elf *.s
