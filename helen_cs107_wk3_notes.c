#include <stdio.h>
#include <stdlib.h>

/*
1. C Pointers
  Just a number indicating memory addresses. Myth machines pointers are 8-byte long
  Pointers are reference to values. One pointer can refer to any size data stucture
  allows reserving new memory during a program
  allows refering to a particular element in an array generically
  dereferencing NULL pointers or bogus addresses result in seg fault
*/
int x = 7;
int *xptr = &x; // pointer to x
printf("address of x: &p\n", xptr);
printf("x via dereferencing xptr: %d\n", *xptr);
int **xptrptr = &xptr; // pointer to xptr

char *str = "CS107";
char **strptr = &str;
char mystery = **strptr;
printf("Mystery: %c\n", mystery); // prints out 'C'

// Double pointers
// write a function that returns the char in a string pointed by p, and updates string ptr to point to the next char
char* next(char** p) {
  char next = *(p)[0];
  *(p)++; // string ptr getting updated
  return next;
}

char* pB = "hello";
printf("next(&pB): %c\n", next(&pB));


/*
2. Arrays in C
  continuous blocks of memory with a fixsed length. 
  Not pointers, you can't change what it points to.
  Access elements like arr[2] or *(arr + 2)
  A pointer to an array points to the first element in the array
  Pointer arithmetic
    - plus, minus ++ means incrementing address by size of an element of type of array, compiler knows how wide the type is.
  You can't get the size of an array after you pass it in a function
  ! Arrays are passed by reference, means passing a pointer. So you can modify the elements passed in; use const to avoid.
  C doesn't check for end of array, can walk off the end
  char *argv[] is an array of pointers
*/
short arr[] = {1, 2, 3}; // each elements take up two bytes each; if 1 at 0x80, 2 would be at 0x82
int nelems = sizeof(arr) / sizeof(arr[0]); // sizeof gives total num of bytes in the array, not true for pointers
size_t *arrptr = arr; // returns the address of a[0]
// These expressions print out the same address: arrptr, arr (decaying), &arr[0], &arr (bad code)
printf("%d", *arrptr++); // * takes precedence. dereference arrptr and return the value, then increment the pointer value for arrptr

void *memcpy(void *dst, const void *src, size_t n); // src and dst may not overlap, copies n bytes from memory area src to memory area dst
void *memove(void *dest, const void *src, size_t n); // allows overlapping memory areas. not as fast as memcpy

char s1[] = "string in an array"; // allows modifying, declaration of a string as array
char *s2 = "string literal with pointer"; // no modifying, attempt would result in seg fault

// swap function for array, sets values directly
void swapA(int *arr, int index_x, int index_y) { // first arg identical to arr[], because once you pass in an array to a function in c, you get a ptr to the first elem in the arr
  int tmp = *(arr + index_x);
  *(arr + index_x) = *(arr + index_y);
  *(arr + index_y) = temp;
}
// can do same ting with memmove
void swapB(int *arr, int index_x, int index_y) {
  int tmp;
  memmove(&tmp, arr + index_x, sizeof(int)); // this works because we know the size of the elements in the array, int
  memmove(arr + index_x, arr + index_y, sizeof(int));
  memmove(arr + index_y, arr + index_x, sizeof(int));
}
// Now, don't swap values directly but swap pointers. 
// look at argv which is an array of char*. write a fucntion to swap two pointers in the array
void swapC(char** arr) {
  char* tmp = *(arr + index_x);
  *(arr + index_x) = *(arr + index_y);
  *(arr + index_y) = temp; // very similar to swapA, but faster since we are only swapping pointers.
}


/*
3. x86-64 Memory Layout
  2 different areas of memory: stack & heap
    -> every program by default has access to 8Mb of stack memory, stack grows downwards. When exceeds its amount, stackoverflow.
    -> shared library/data
    -> heap, program requests memory frmo the operating system (malloc, calloc, realloc, free). grows upwards
    -> global data
    -> text (machine code)
  Stack allocation
    - local variables and arrays kept on the stack
  Parameters
    - parameters can be put on the stack, and behave like local variables.
  Why we like stack allocation
    - fast. Allocating space on the stack is efficient because your program already has access to the memory.
    - convenient. The scope (lifetime) of the data is inside the function, so it keeps things tidy.
    - type safety. You are controlling the type of the variables, and therefore the compiler can do lots of checks on the data. not always the case with heap memory.
  Why we don't like stack allocation
    - isn't that plentiful
    - size fixed at declaration, no option to resize
    - limited scope
  Dynamic allocation
    - in C++ when you use new and delete
    - malloc, memory allocation for a specified number of bytes. returns ptr. if malloc return NULL, not enough memory to request.
    - free, ptr must point to a previously allocated block (or it can be NULL). Once a program frees memory, it cannot be used again. 
      The pointer can be used to point elsewhere.
    - calloc, contiguously allocates space for count objects that are size bytes of memory each returns a pointer to the allocated memory is filled with bytes of value
  Why we like heap allocation
    - plentiful.
    - Allocation and deallocation are under the program's control — you can precisely determine the lifetime of a block of memory.
    - can resize
  Why we don't like heap allocation
    - only moderately efficient
    - low type safety
    - memory management is tricky. initialize, keep track of amount of bytes requested, free but not free twice.
    - leaks possible
  When is heap allocation required
    - very large allocation
    - dynamic construction
    - need to control lifetime - memory must persist outside of function call
    - need to resize memory after initial allocation
  .valgrind is your friend.
*/
int scores = malloc(20 * sizeof(int)); // 20 integers. malloc works in bytes
int scores = calloc(20, sizeof(int)); // diff: it zeros out the memory for you.

void* malloc(size_t size);
void* calloc(size_t count, size_t size); 
void* realloc(void *ptr, size_t size);
void free(void *ptr); // undefined behavior on non-heap address.


/*
4. Assignment tips
  const char* (and const char **, const char ***, etc) 
    - mean the characters at the location ultimately being referred to cannot be modified, but any pointer on the way there can be modified. 
  
  Environment variables 
    - live inside your terminal session
    - used to let the shell know how to execute certain programs. can access them in c program
  Unix printenv
    - third parameter for main() to take in: const char* envp[]. No count, we loop through it until a NULL entry marking its end
    - Each element in envp is a string of the form KEY=VALUE. need a bit of processing to separate name and value
  Unix which // we will write which 
    - used to identify the location of a given executable
    - When type which ls, terminal goes through each of the paths in the PATH variable and search the ls executable
  Unix printenv PATH
    - colon delimited list of filepaths
  Change environment variable for 1 iteration
    - env VARNAME=custom_value ./my_executable
  Unix access / acess library function
    - int access(const char *pathname, int mode);
    - access [-rwxF] file
    - "mode" is a bitwise OR of the constants F_OK, R_OK, W_OK, and X_OK, which represent the existence, read, write, and execute permissions
    - The function returns 0 if the file exists and the requested permissions are granted, otherwise it returns -1 and sets the errno variable to indicate error
    
    
  Design issues of strtok()
    - strtok modifies the passed-in input, so we cannot pass in read-only strings
    - strtok can only manage one active tokenization at a time. 
      starting a second tokenization before finishing the first will delete the saved state of the first and replace it with the second.
    - thus, when we write scan_token, we don't use static/global varisables, and do not modify the input string
  Documentation
    - When functions have assumptions, limitations or flaws, documentation should make these clear.
    - goal for manual page reference should be that a client can effectively use your function without seeing the code, 
      just like how you can use string functions without seeing their implementations.
          
          scan_token DOCUMENTATION
          
          NAME
              scan_token - # TODO write a one-sentence description of scan_token
              bool scan_token(const char **p_input, const char *delimiters,
                              char buf[], size_t buflen);
                              
          ARGUMENTS
              const char **p_input - #TODO: write one sentence explaining the p_input argument
              const char *delimiters - #TODO: write one sentence explaining the delimiters argument
              char buf[] - #TODO: write one sentence explaining the buf argument
              size_t buflen - #TODO: write one sentence explaining the buflen argument
              
          RETURN VALUE
              #TODO: write a 1-3 sentence description of the possible return values of scan_token.
              Make sure to include a description of what will be stored in the buf argument upon return.
              
          ASSUMPTIONS
              #TODO: write 2-5 sentences explaining the assumptions made by your scan_token function.
              Here is an example: The scan_token function assumes that the buf argument
              has space for buflen characters.
              
          DESCRIPTION
              #TODO: write one paragraph explaining the implementation of your scan_token function.
              This section should include (high-level) implementation details. You can use your function-header
              comment as a starting point for this section.
  */
const char* user_name = get_env_value(envp, "USER"); // we'll write get_env_value
if (user_name != NULL) {
  printf("Hello, %s!", user_name);
}

#include <assert.h>
assert(expression);
