
/*
1. More Assembly
  - colon : is label, indicates function call in Assembly
  - First parameter in %rdi
  - Lea instruction (load effective address)
      Related to mov, think of it as the & in C. It retrieves the address of the memory location
      lea S, D = &S -> D
  - Push and pop on the stack, modify %rsp
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
    Binary instructions (register or memory, but not both)
      add S, D = D ⟵ D + S Add
      sub S, D = D ⟵ D - S Subtract
      imul S, D = D ⟵ D * S Multiply
      xor S, D = D ⟵ D ^ S Exclusive-or
      or S, D = D ⟵ D | S Or
      and S, D = D ⟵ D & S And
    Shift instructions (first operand is either amoung of shifting, or %cl)
      sal k, D = D ⟵ D << k Left shift, same as shl
      sar k, D = D ⟵ D >> k Arithmetic right shift (take sign into account)
      shr k, D = D ⟵ D >> k Logical right shift (always fill in with 0)
    Special multiplication instructions
      imulq S = R[%rdx]:R[%rax] ⟵ S × R[%rax] Signed full multiply
        if you are multiplying 2 64bits, you get 128 bit to hold your answer 
        typedef unsigned __int128 uint128_t
        put one value in %rax and mul the other value
        imul would just truncate the answer
      mulq S R[%rdx]:R[%rax] ⟵ S × R[%rax] Unsigned full multiply
    Special divison operations
      cqto = R[%rdx]:R[%rax] ⟵ SignExtend(R[%rax]) Convert to oct word
      idivq S = R[%rdx] ⟵ R[%rdx]:R[%rax] mod S; Signed divide
                R[%rax] ⟵ R[%rdx]:R[%rax] ÷ S
      divq S = R[%rdx] ⟵ R[%rdx]:R[%rax] mod S; Unsigned divide
               R[%rax] ⟵ R[%rdx]:R[%rax] ÷ S
                 
  Control
    4 flags
      CF: Carry flag. The most recent operation generated a carry out of the most significant bit. Used to detect overflow for unsigned operations.
      ZF: Zero flag. The most recent operation yielded zero.
      SF: Sign flag. The most operation yielded a negative value.
      OF: Overflow flag. The most recent operation caused a two's-complement overflow—either negative or positive.
    For logical operations (e.g., xor), the carry and overflow flags are set to 0.
    For shift operations, the carry flag is set to the last bit shifted out, while the overflow flag is set to zero. inc and dec set the overflow 
    and zero flags, but leave the carry flag unchanged
    
  cmp and test
    They set condition flags without altering any other registers,
    CMP S1, S2 = S2 - S1 Compare
    TEST S1, S2 = S2 & S1
    Usage
      We can set a single byte to 0 or 1 depending on some combination of the condition codes.
      We can conditionally jump to some other part of the program.
      We can conditionally transfer data.
      jmp Label = direct uncodnditional jump
*/

/*
2. Helpful tools in assembly deciphering
  godbolt.org
  
  gdb commands
    display/4i $rip: This command displays four assembly instructions at once after each step. $rip points to the next instrutcion that's about to run.
    si: This command steps one assembly instruction at a time
    disas function_name: This will disassemble an entire function for you.
    p $rax: This prints the value of $rax.
    p *(char **)($rsp): This dereferences a char ** pointer in $rsp and printsthe string value.
  • p *(char **)$rsp@10: If $rsp points to the start of an array, this will print out the first ten elements in the array!
  stepi, nexti
  info reg
  layout split
*/
