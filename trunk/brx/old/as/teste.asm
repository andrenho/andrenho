%define NUMBER 0x40

  jmp     teste
  load.8  $a,$b,$c

  ; line test
teste:
  and     $a,$b,NUMBER
