%include "hippo.asm"

	org 0x1000
                                ; addrmode  addr  opcodes

	ld A, 0			; imm       1000  01 00 00
next:
	ld B, [A+hello]		; ind       1003  06 10 10 14
	bz B, stop		; dir       1007  83 11 0B
	st [A+VIDEO], B         ; ind       100A  0D 01 01 00
	inc A                   ; imp       100E  41 00
	jmp next                ; rel       1010  4C 0D

stop:
	jmp stop                ; rel       1012  4C 02


hello db "Hello world!", 0      ;           1014
