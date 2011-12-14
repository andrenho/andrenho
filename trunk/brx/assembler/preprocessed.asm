%line stdin 1
%line defines.asm 1
%line defines.asm 1
 %line stdin 1
section .code 
 %line stdin 2
jmp start  
 %line stdin 3
nop 
 %line stdin 4

 %line stdin 5
 
 %line stdin 6
start: 
 %line stdin 7
load.8 $a , $b , 0x40 
 %line stdin 8
 