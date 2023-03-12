/*
1. Optimization
Premature optimization is the root of all evil. -- Knuth

Considerations
  Time the code to see if it works fine at the scale you care about.
  Use the correct algorithm. We're not fixing big O here.
  Keep it simple.
  Let gcc do its optimizations.
  Optimizae explicitly as a last resort.
  
When 2 ptrs passed into a function, think: If 2 ptrs are the same does it make a difference?
e.g., *xp += *yp; *xp += *yp; is not the same as *xp += 2 * *yp;
Point is, whenever if you have this sort of situation, the compiler would not optimize.

compiler does these
  Constant folding
  Common subexpression elimination
  Strength reduction
    - The compiler replaces expensive (strong) operations (e.g., multiply, divide) with equivalent expressions that are less strong.
  Code motion
    - The compiler moves code out of loops if it can, to only perform the operation once.
  Dead code elimination
    - The compiler realizes that most of the code does not perform useful work, so it just removes it.
    
gcc (GNU compiler optimization)
  -O0 // faithful, literal match to C, good for debugging, everything goes on the stack.
  -Og // debug-friendly
  -O2 // apply all acceptable optimizations
  -O3 // even more optimizations, relies strongly on exact C specifications (e.g., signed assumed to not overflow)
  -Os // optimize for code size, perform the -O2 optimizations that don't increase the code size (e.g., function alignment). To make stuff fit in memory
  
-Q --help=optimizers
  See the exact set of optimizations that are enabled at each level.
  
How to measure performance
  valgrind --tool=callgrind

Hand optimization
  removing function calls
  keep a local copy of the variable, and don't write to the memory every time, just write to memory once at the end.
  
Caching ang locality
  registers -> 2 L1 cahes -> L2 cache -> L3 cache -> main memory -> disk
  Computers have many levels of memory. Memory goes from really fast (registers) to really slow (disk)
  As data is more frequently used, it ends up in faster and faster memory.

Callgrind
  Process file to see source annotated with count per line
  callgrind_annotate --auto=yes callgrind.out.<pid>
    Callgrind is a profiling tool that can count function calls and the CPU instructions executed within each call, 
    and it can also simulates the L1/L2 caches and counts cache misses/hits. It outputs a file named callgrind.out.[process id]. 
    Then, one can run callgrind_annotate to display the information in the out file in a meaningful way.
*/

/*
2. C directives
  #include
    C90 standard headers list
      <assert.h> <ctype.h> <errno.h> <float.h>
      <limits.h> <locale.h> <math.h> <setjmp.h>
      <signal.h> <stdarg.h> <stddef.h> <stdio.h>
      <stdlib.h> <string.h> <time.h>
  
  # pragma
    request special behavior from compiler
    - once: if seen when scanning a header file, that file will never be read again
  
  # define
    defines a macro. 
    macro name followed by a space is a constant/literal
      #define PI 3.14
    macro name followed by parenthesis is a function-like macro (always good idea to use extra parenthesis)
      #define ABS_VAL(x) (((x)<0 ? -(x) : (x)))
    Can produce unexpected results if not done right since macros are textual substitution to source code.
    Prefer to use language features like const int, or enum
  
  #error
  #warning
*/
