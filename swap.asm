// Program: swap.asm
// Usage: put values in RAM[0], RAM[1]

//swap the values of RAM[0] and RAM[1]
 @1  
 D=M
 @16
 M=D

 @0  
 D=M
 @R1  
 M=D

 @16  
 D=M
 @R0
 M=D
