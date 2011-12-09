%define bbb ccc
%include teste2.asm

  bbb
  nop
  data  "asdas",$af,12,'d'
  sum   $a, $b, $c  ; comment

%func fct x,y
  mov a,x,y
%endfunc
