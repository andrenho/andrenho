// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[3], respectively.)

// Put your code here.

  D = 0   // D = current sum
  @1
  A = M   // A = RAM[1]

(LOOP)
  A       // if d == 0 goto END
  @END
  0;JEQ

  @0
  D = D+M

  @LOOP   // goto LOOP
  0;JMP
(END)

  @2
  M = D
