#include <iostream>
using namespace std
  
  /*
  1. assignment tips
    Declaring a literal (when you want something different from the default)
      - put a U after a number literal to make it unsigned. For instance, 1U means the literal 1 as an unsigned number.
      - put an L after a number literal to make it a long (64 bits)
    Unix tool (gdb)
      - print
          gdb p print command defaults to decimal format. 
          use p/format to instead select other formats such as x for hex, t for binary, and c for char, u for unsigned decimal, d for signed decimal
      - examine
      - to run: type gdb executable_name -> run arg1 arg2
      - break
          to break at the beginning of the function named main: break main
          to set a breakpoint at line 47 in myprogram.c: break myprogram.c:47
          each breakpoint is sequentially assigned a number, to remove: delete 2
          to see info about break point: info break
          conditional break: [BREAKPOINT] if [CONDITION]
          once stopped, can c continue, n for next, or s for step
      - use the backtrace command to get a full stack trace of the program's execution when the error occurred
      - info
          info args prints out the arguments (parameters) to the current function you're in
          info locals prints out the local variables of the current function
      - stack frames
          up moves you up one stack frame, similarly down
          helpful if you're stuck at a segfault and want to know the arguments and local vars of the faulting function's caller
    Bitwise tips
      - & often used for isolating, | often used for adding in bits, ^ often used for toggling, ~ invert bits
  */
