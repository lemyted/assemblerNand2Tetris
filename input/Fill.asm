// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

(MAIN)
  // init R0 to zero
  @R0
  M=0

  // init R1 to zero
  @R1
  M=0
 
  // init PXC (pixel counter)
  @R0
  D=M
  @PXC
  M=D

  // init CLR (color)
  @R1
  D=M
  @CLR
  M=D

  // assign value to PXC
  @SCREEN
  D=A
  @PXC
  M=D
  
  // assign value to CLR
  @KBD
  D=M
  @CLR
  M=D 

  // fill if CLR is 1 or else unfill
  @FILL_UNFILL
  0;JMP
  
(FILL_UNFILL)
  
  // get color
  @CLR
  D=M

  // choose to go to black or white
  @WHITE
  D;JEQ
  
  (BLACK)
    // set PXC as current address
    @PXC
    A=M

    // set color to current address
    //M=D
    D=M
    
    // set pixel black
    D=-1
    @LOOP
    0;JMP

  (WHITE)
    // set PXC as current address
    @PXC
    A=M

    // set color to current address
    //M=D
    D=M

    D=0

  (LOOP)

    // set PXC as current address
    @PXC
    A=M

    // set memory of current pixel
    M=D

    // increment PXC
    @PXC
    M=M+1

    // check if memory in scope of screen matrix
    @PXC
    D=M
    @SCREEN
    D=D-A // remove offset of screen memory
    @8192 // screen matrix size
    D=A-D

    // go to main if done
    @MAIN
    D;JLE

    // loop
    @FILL_UNFILL
    0;JMP  
