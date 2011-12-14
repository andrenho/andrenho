%line stdin 1
%line defines.asm 1
%line defines.asm 1
 %line stdin 1
org 0xf000 
 %line stdin 2

 %line stdin 3
section .code 
 %line stdin 4
jmp start  
 %line stdin 5
nop 
 %line stdin 6

 %line stdin 7
 
 %line stdin 8
start: 
 %line stdin 9
load.8 $a , $b , 0x40 
 %line stdin 10
 