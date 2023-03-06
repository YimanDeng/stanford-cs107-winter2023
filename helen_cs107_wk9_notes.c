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
*/

/*
# pragma
*/
