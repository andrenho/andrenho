%define start 5
%line stdin 0x1 
 %line defines.asm 0x1 
 %line defines.asm 0x1 
 %line stdin 0x1 
 section .code 
 %line stdin 0x2 
 jmp start 
 %line stdin 0x3 
 nop %line stdin 0x4 
 
 %line stdin 0x5 
 
 %line stdin 0x6 
 
 %line stdin 0x7 
 load.8 $a , $b , 0x40 
 %line stdin 0x8 
  