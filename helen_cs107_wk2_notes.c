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
  
  /*
  2. C char
    ascii 
      - 8-bit encoding
    UTF-8 
      - assign each code value an unsigned byte sequence of one to four bytes in length
      - backward compatibility with ascii, chars in the ASCII encoding have the same encoding in UTF-8
      - a char's code point is commonly written in the format U+NNNN, which signifies the hexadecimal value 0xNNNN
      - U+0000 ~ U+007F | 1 byte long
        U+0080 to U+07FF | 2 bytes long
        U+0800 to U+FFFF | 3 bytes long
  */
  #include <ctype.h>
  isalpha(); isdigit(); isspace(); ispunct(); isalnum(); isascii(); islower();  // returns zero if the character tests false and returns non-zero if the character tests true.
  toascii(); tolower(); toupper();

  /*
  3. C string
    is: a sequence of chars, followed by terminating 0 called a "null" byte \0
    referenced by: 
      - pointer to its first character
      - array variable that's converted to a pointer when accessing the elements
    comparing c strings
      - comparing by pointer values only returns if one address is before the other, use strcmp() instead
  */
  char *s1 = "cat";
  char *s2 = s1; // not a copy! points to same address as s1
  #include <string.h> // all have worse-case complexity of O(n). strings are not objects with embedded information
  size_t strlen(const char *str); // size_t is the type of the result returned by sizeof operator, usually used for variables that models size or index of an array
  int strcmp(const char *s, const char *t); // compare 2 strings alphabetically char by char, return 0 is identical, <0 if s<t, othersie >0
  int strncmp(const char *s, const char *t, size_t n); // stops after n chars and doesn't traverse past null char
  char *strchr(const char *s, int ch); // returns pointer to the first occurrence of a char in s, NULL is char not in string
  char *strstr(const char *haystack); // returns pointer to the first occurrence of needle in haystack, NULL if no needle
  char *strcpy(char *dst, const char *src); // copies src to dst. Beware of "buffer overflows," dst needs to have enough space
  char *strncpy(char *dst, const char *srs, size_t len); // if no null byte in first n char of src, dst will NOT be null-terminated
  char *strcat(char *dst, const char *src); // append src onto end of dst, dst always null-terminated
  char *strncat(char *dst, const char *arc, size_t n); // only copies n chars
  size_t strspn(const char *s, const char *accept); // returns length in bytes of initial part of s which only contains chars in accept
  size_t strcspn(const char *s, const char *reject); // opposite of strspn, c stanfords for complement
  char *strdup(char *s); // allocates memory on the heap, copies s, returns pointer to copy. Need to be freed by free(char *copy)
  char *strndup(char *s); // copy up to n chars, always null-terminating
