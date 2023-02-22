#include<stdio.h>
#include<stdlib.h>
/*
1. Floating point numbers
  How to represent real numbers in a computer?
  Constraints: 
    Want fixed number of bits. So we can't represent a number exactly.
    Want to represent a large range of numbers
    Want to be able to do operations on the numbers
  Fixed point:
    e.g., 10^2, 10^1, 10^0, 10^-1, 10^-2. Arithmetic is pretty simple. But range is 0 to 999.99. The range is set by where we fix the decimal place.
  Floating point:
    V = x * 2^y. exponent and fractional value
    Fractional values in binary, similar https://web.stanford.edu/class/cs107/float/
    Interesting, .1 in binary fraction is like 1/3 in decimal fraction, .1 repeats like 0.000110011...
    Left and right shift of binary point - the number is divided or multiplied by 2
    0.1111111... is the number just below 1, i.e., 1 - epsilon
  IEEE floating point: 
    V = (-1)^s * 2^E * M
    sign bit s is 1 or 0
    scaling factor E weights value by power of 2. 
    Mantissa M is the digits of the number, is a fractional binary value that ranges either between [1, 2 - epsilon] or [0, 1 - epsilon]
    For single, 1 + 8 + 23 = 32 bits
    For double, 1 + 11 + 52 = 64 bits
  You don't want to use floating point for something like banking
  
  A float is normalized if the exponent is not all 1s and not all 1s
  exponent value is signed exponent in biased form: value - (2^k - 1) = actual exponent, e.g., 126-127 = -1.
  fraction f represents 0.f1f2f3... with implied leading 1
  
  When is floating point number an integer? the fractional part of the significand is equal to 0
  When exponents is all zeros, denormalized, the bias is now 1 less, the significand value now without the leading 1.
  0 represented with all 0s.
  When exponents all ones, exceptional form 0 1...1 0...0 is +infinity, sign bit 1 is -infinity
  Eceptional numbers also define NaN, not a number.
  
  Arithmetic with floating point numbers
    not enough precision if you try to do between 2 numbers of very different orders
    0.1 + 0.2 != 0.3
    float equality, sometimes you can't differentiate 2 different numbers due to pimited precision
*/
float f = 0.1; 
// print with 27 decimal places
printf("%.27f\n",f);

/*
2. Assembly language
  The textual representation of the machine code. Computers understand Assembly code
  The compiler gcc generates assembly code from C code. Assembly then converted to machine level code.
  No types. Unique to the processor. The one we use on the Myth machines is x86.
  Machine level code is based on "instruction set architecture"
  
  Things hidden in c:
    - %rip the program counter, register instruction pointer, a number indicating address of next instruction. 
      16 locations each 8-byte. They are not in main memory, do not have address, cannot pass in a pointer
      Can hold address or int values.
      Registers are used for arithmetic, local variables, and return values for functions
      Condition code register, holds status info on most recent aristhmetic/logical instruction.
    - Return values goes into a register %rax
    - No different data types
      A single machine instruction performs only a very elementary operation. Add, transfers data, conditionally branches
    - emacs hello.s
    - Unix disas main
    
  Intel data foramts
    - word, 2-byte, w
    - double words, 4 byte, l
    - long, quad words, 8 bytes, q
   
  Registers
    - Starts with r, %ax, %bx, %cx, %dx, %si, %di, %bp, %sp
    - More added, %r8, ..., %r15
    - %rsp, stack pointer
    - 1st 2nd 3rd argument into %rdi, %rsi, %rdx
    - Integer registers are nested
        e.g., %rax, %eax, %ax, %al, these are on the same register, just different parts
  
  $number means "the literal number"
  
  Operand forms
    - Imm(rb, ri, rs) = Imm + R[rb] + R[ri] * s, then you dereference
    - Similarly, move 4(%rax) ... means *(%rax + 4)
    - immediate value, 2 register values, 1 scaling factor
  
  Data movement instructions
    - When moving, we are making the copy. The data is still in still inside the sources.
    - mov　source and dest, at most 1 can be a memory address. 
    - movl (4 bytes zeroes out upper bits), movw (2 bytes), movb (1 bytes), movq (8 bytes)
    - movabsq (used when 64bit immediate value needed in a register, regular movq can only take 32 immediate value)
    - From smaller to larger source
      movz (zeros out the upper bits)
      movs (fills the remaining bytes by sign-extending the most significant bit in the source)
  When we have a parenthesis, we take what's in the register, and interpret it as a pointer value.
*/ 

/*
3. Assignment tips
  The bsearch() function searches an array of nel objects, the initial member of which is pointed to by base, for a
  member that matches the object pointed to by key.  The size (in bytes) of each member of the array is specified by
  width. Returns a pointer to a matching member of the array
  
  gdb print out an array
    p FIRST_ELEM@COUNT where FIRST_ELEM is the first element to print and COUNT is the count of elements to print.
    
  scandir
    dirent struct is directory entry, has field char d_name[] to store the filename.
    `dirp`: The path of the directory to be scanned
    `namelist`: A pointer to an array of struct dirent pointers. The scandir function allocates memory for this array and populates it with pointers to directory entries.
    `filter`: A pointer to a function that is used to filter the directory entries. If this argument is NULL, all entries are included in the result.
    `compar`: A pointer to a function that is used to sort the directory entries. If this argument is NULL, the entries are not sorted.
    returns the number of entries in the directory, -1 on error
    user needs to free namelist entries and namelist.
    Filter: A non-zero return value indicates that the entry should be kept, and a zero return value indicates that the entry should be discarded.
  
  typedef function pointers
    When we define int_func_t as typedef int (*int_func_t)(int);, we are defining a new type int_func_t as a pointer to 
    a function that takes an int argument and returns an int.
*/
#include <dirent.h>
int scandir(const char *dirp, struct dirent ***namelist, int (*filter)(const struct dirent *),
              int (*compar)(const struct dirent **, const struct dirent **));



void* bsearch(const void *key, const void *base, size_t nel, size_t width, int (*compar) (const void *, const void *));
