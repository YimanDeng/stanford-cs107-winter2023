
/*
  1. 
    : colon is label, indicates function call in Assembly
    first parameter is always stored in %rsp
  Lea instruction
    Related to mov, think of it as the & in C. It retrieves the address of the memory location
  Push and pop on the stack
    Stack grows downwards
    Push changes the stack pointer -8, then put the thing in memory
      pushq %rbp = 
      subq $8, %rsp
      mov $rbp, (%rsp)
    Pop
      popq %rax = 
      movq (%rsp), %rax
      addq $8, %rsp
    Unary instructions (act on single memory/register)
      inc D, dec D, neg D, not D
*/
