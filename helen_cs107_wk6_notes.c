
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
    
  Arithmetic
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
    Conditional moves
      cmove S, R
      Runs faster than jumps since jumps are bit expensive for registers.
    For loops
      If/while loops conditionals are done via jumps
      for loop is while loop in disguise

  Procedures (Functions)
      1.Pass control: update the program counter (%rip) to the start of the function, 
      and then at the end of the function, set the program counter to the instruction after the call.
      2.Pass data: P must be able to provide parameters to Q, and Q must be able to
      return a value back to P.
      3.Allocate and deallocate memory: Q may need to allocate space for local
      variables when it begins, and free the storage when it returns. (generally on the stack)
    The Runtime stack
      Frame for calling function P
        Earlier function higher on the stack
        Argument 7-n
        Return address (the address after the fn call address)
      frame for executing function Q.
        Saved registers
        Local variables
        Argument build area
      -> %rsp, Stack "top"
    Some function don't even need a stack frame.
    When P calls Q, The next instruction in P after the call is pushed onto the stack (return address),
    the program counter is set to the first instruction in Q. When Q executes a ret instruction, 
    the return address is popped off the stack and %rsp is set to that value.
    
  Caller vs callee owned registers
    For caller owned registers, e.g., %rbx, you are expected to keep the value in it unchanged when calling a function.
    Done thru push %rbx at the start and pop %rbx at the end
    
  Recursion
*/

/*
2. Helpful tools in assembly deciphering
  godbolt.org
  
  gdb commands
    display/4i $rip
      Displays four assembly instructions at once after each step. $rip points to the next instrutcion that's about to run.
      undisplay xxx
    x/1gx $rsp 
      print out the 8 byte value at the top of the stack. ("Examine (1) (g)iantword in he(x) starting at $rsp")
    display/x *(long *)$rsp@5
      display what 5 values are stored on the stack right now
    si
      This command steps one assembly instruction at a time
      stepi, nexti
    disas function_name
      This will disassemble an entire function for you.
    p
      p $rax: This prints the value of $rax.
      p *(char **)($rsp): This dereferences a char ** pointer in $rsp and printsthe string value.
      p *(char **)$rsp@10: When interpreting $rsp as a pointer to an array of char*, this will print out the first ten elements in the array!
      p ((int *)$rdi)[0]@$rsi // $rsi stores the length of the array
    info reg
    layout
      layout split
      layout source
      layout asm
      layout reg change the UI to also show the values of registers
      come back using ctrl-xa
      ctrl p or n to have previous or later commands
    finish
      finishes execution of the current function and returns to the calling function.
    b
      break *0x401368
      break on individual Assembly instruction
      break [BREAKPOINT] if [CONDITION]
    watch
      a special kind of breakpoint that stops your program whenever there is a change in the value of that expression 
      or a write to that memory location.
    <CTRL+L> 
      repaint the screen to clear any visual artifacts that occur
    objdump
      objdump -d [filepath] > [filename].s
    nm
      use the nm utility (nm vault) to print what's called the "symbol table" of the executable, 
      which contains the names of functions and global variables and their addresses.
    strings
      use the strings utility (strings vault) to print all the printable strings contained in the executable
*/

/*
3. Vulnerabilities
  - Use after free: If you have a pointer pointign to a block of memory that has already been freed.
    Undefined behavior.
  - buffer overflow
  How to act
    responsive disclosure
    full disclosure (0-day)
  Case study: EternalBlue
*/

/*
4. Assignment Tips

 
 
*/
