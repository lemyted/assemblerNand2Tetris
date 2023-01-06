@R2 // is here
M=0

(MAIN)
  @IS_R0_VALID
  0;JMP
  @IS_R1_VALID
  0;JMP
  @MULT_LOOP
  0;JMP

(IS_R0_VALID)
  @R0
  D=M
  @FINISH
  D;JLE

(IS_R1_VALID)
  @R1
  D=M
  @FINISH
  D;JLE

(MULT_LOOP)
  // increment R2
  @R2
  D=M
  @R0
  D=D+M
  @R2
  M=D

  // decrement R1
  @R1
  M=M-1

  // loop
  @MAIN
  0;JMP

(FINISH)
  // clean R0
  @0
  M=0
  @END
