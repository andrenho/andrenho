DEVICE=atmega8
PROGRAMMER=avrisp
SPEED=19200
#DEVICE=atmega328p
#PROGRAMMER=arduino
#SPEED=115200

all: main.hex

main.elf: main.c
	avr-gcc -mmcu=$(DEVICE) -Wall -Wextra -Os -omain.elf main.c

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex

assembly: main.c
	avr-gcc -S -mmcu=$(DEVICE) -Wall -Os -omain.s main.c

upload: main.hex
	avrdude -p$(DEVICE) -c$(PROGRAMMER) -b$(SPEED) -P/dev/ttyACM0 -U flash:w:main.hex
	# -C C:\temp\arduino-1.0.4\hardware\tools\avr\etc\avrdude.conf

fuse:
	#avrdude -p$(DEVICE) -cstk500v1 -P/dev/ttyACM0 -b19200 -e -Ulfuse:w:0xFF:m -Uhfuse:w:0xD9:m
	avrdude -p$(DEVICE) -cstk500v1 -P/dev/ttyACM0 -b19200 -e -Ulfuse:w:0xe4:m -Uhfuse:w:0xD9:m

clean:
	rm -f *.hex *.elf *.s
