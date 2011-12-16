%define start 61445
%line stdin 0x1 
 %line defines.asm 0x1 
 %line defines.asm 0x1 
 %line stdin 0x1 
 %line stdin 0x2 
 
 %line stdin 0x3 
 section .code 
 %line stdin 0x4 
 jmp start 
 %line stdin 0x5 
 nop 
 %line stdin 0x6 
 
 %line stdin 0x7 
 
 %line stdin 0x8 
 
 %line stdin 0x9 
 load.8 $a , $b , 0x40 
 %line stdin 0xa 
 
 %line stdin 0xb 
 db "Teste" , 0x42 
 %line stdin 0xc 
  