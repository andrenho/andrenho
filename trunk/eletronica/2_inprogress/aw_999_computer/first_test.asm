org 0x1000

	ld A, hello
	ld B, VIDEO
next:
	ld C, [A]
	bz C, stop
	ld [B], C
	inc A
	inc B
stop:
	jmp stop


hello db "Hello world!", 0
