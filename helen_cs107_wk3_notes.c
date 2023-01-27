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
    - malloc, memoery allocation for a specified number of bytes. if malloc return NULL, not enough memory to request
    - free, ptr must point to a previously allocated block (or it can be NULL). Once a program frees memory, it cannot be used again. 
      The pointer can be used to point elsewhere.
*/
int scores = malloc(20 * sizeof(int)); // 20 integers. malloc works in bytes
int scores = calloc(20, sizeof(int)); // diff: it zeros out the memory for you.

void* calloc(size_t count, size_t size);
void* malloc(size_t size);
void* realloc(void *ptr, size_t size);
void free(void *ptr);
