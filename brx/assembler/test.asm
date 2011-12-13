%include "defines.asm"

section .code
	jmp	start		; jump to start
	nop

; start of code
start:
	load.8	$a, NUMBER
