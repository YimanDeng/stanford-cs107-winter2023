#include <stdio.h>
#include <stdlib.h>

/*
1. C pointers
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
  When doing pointer arithmetic, ++ means incrementing address by size of an element of type of array, compiler knows how wide the type is.
  You can't get the size of an array after you pass it in a function
  Arrays are passed by reference, means passing a pointer. So you can modify the elements passed in; use const to avoid.
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
