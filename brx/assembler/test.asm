%include "defines.asm"

	org	0xf000

section .code
	jmp	start		; jump to start
	nop

; start of code
start:
	load.8	$a,$b,NUMBER

	db "Teste", 0x42
