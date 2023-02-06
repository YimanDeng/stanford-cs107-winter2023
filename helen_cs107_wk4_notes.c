#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
1. Generic Pointers
  void * pointer
    - Doesn't have a width associated with the underlying data based on type.
    - Can pass void* pointers to and from functions, and can assign them values with the & operator.
    - Cannot dereference a void pointer, no [0]. Can't ++, compiler doesn't know type to do pointer arithmetic.
  Why?
    - Sometimes we want to write a generic function to deal with any type. e.g., void free(void *ptr).
  Function pointers: 
    - How to print a void *element?
    - In C, can pass function pointers as parameters to other functions
    - void (*myfunc) (int), declare myfunc as pointer to function (int) returning void
      // cdecl.org, or cdecel explain on Myth
*/

// program to swap first and last element in an array.
void swap_ends(void *arr, size_t nelems, int width) { 
  // allocates space for the copy
  char tmp[width]; // char is 1 byte, width is in bytes. tmp can store 1 elem in the array
  // copy the first element to tmp
  memmove(tmp, arr, width);
  // copy the last elem to the first
  memmove(arr, (char *)arr + (nelems - 1) * width, width); // casting required 
  // copy tmp to the last element
  memmove((char *)arr + (nelems - 1) * width, tmp, width);
}

// a C idiom
for (size_t i=0; i < nelems; i++) {
  // get ith element
    void *ith = (char *)arr + i * width;
}

/* 
2. Function Pointers
  a variable that stores the address of a function that can later be called through that function pointer
*/
void print_int(void *arr) { // need to create one of these for every type
  int i = *(int *)arr;
  printf("%d",i);
}

void print_array(void *arr, size_t nelems, int width, void (*pr_func)(void *)) { // func ptwr don't need & because it's implied
  for (int i=0; i < nelems; i++) {
    void *element = (char *)arr + i * width;
    pr_func(element);
    i == nelems - 1 ? printf("\n") : printf(", ");
  }
}
print_array(i_array, i_nelems,sizeof(i_array[0]), print_int);

// each one of the void* points to an elem in the array, the int it returns indicates result of comparison
int compar_str(cosnt void *s1, const void *s2) {
  return strcmp(*(char **)s1, *(char **) s2);
}
void qsort(void *base, size_t nelm, size_t size, int (*compar)(const void *, cosnt void *)); 

// can also write a cmp function for rectangle structs
int rect_comp_area(const void *r1, const void *r2) {
  const struct rect *r1ptr = r1; // no cast necessary
  const struct rect *r2ptr = r2;
  int area1 = r1ptr->width * r1ptr->height;
  int area2 = r2ptr->width * r2ptr->height;
  return area1 - area2;
}
void qsort(rec_arr, NUM_RECT, sizeof(rect_arr), rectcmp); 

/*
3. Building a Generic Stack
*/
typedef struct node {
  struct* node next;
  void* data; // must keep track of info of how big data is
} node;

typedef struct stack {
  // everything happens at the top
  node* top;
  int nelem;
  int elem_size_bytes;
} stack;

// now start building some functions
stack* stack_create(int elem_size_bytes) {
  // need to find somewhere to create the stack;
  stack* s = malloc(sizeof(stack));
  assert(s != Null);
  // populate new stack
  s->top = NULL;
  s->nelem = 0;
  s->elem_size_bytes = elem_size_bytes;
  
  returen s;
}

void stack_push(stack* s, const void* data) {
  // in general, make a copy
  node* new_node = malloc(sizeof(node));
  assert(new_node != NULL);
  
  // make space for the data
  new_ndoe->data = malloc(s->elem_size_bytes);
  assert(new_node != NULL);
  memcpy(new_node->data, data, elem_size_bytes);
  
  new_node->next = s->top;
  s_top = new_node;
  s->nelem++;
}

bool stack_pop(stack* s, void* addr) {
  if (s->nelem == 0) return false; 
  
  node* top = s->top;
  memcpy(addr, top->data, s->elem_size_bytes);
  s->top = top->next;
  
  free(top->data);
  free(top);
  s->nelem--;
  return true
}

/*
4. Assignment Tips

Valgrind
  Memory leak
    - didn't free memory you previously allocated
  Memory access
    - read or write memory you don'thave access to
gdb
  help 
    - h [command]
  info 	
    - i [cmd]
    - breakpoints (info breakpoints), local variables (info locals), parameters (info args), breakpoint numbers (info break), etc.
  run
    - r [args]
  next
    - n
    - completely runs functions
  step
    - s
    - may take you into functions you didn't write
  finish
    - runs a function until it completes
  continue	
    - c	
    - continue running the program until the next breakpoint or until the program ends
  print	
    - p [x]
    - print the value of a variable
  display
    - disp [EXP]
    - Print value of expression EXP each time the program stops.
  break
    - b [x]	
    - put a breakpoint in the program at a specified function name / particular line number
  delete
    - d [x]
    - removes the breakpoint with the given number
    - If number omitted, deletes all breakpoints after confirming
  frame
    - select and print a stack frame
  where
    - print backtrace of all stack frames
  backtrace
    - bt
    - print a stack trace to let you know where in the program you are currently stopped
  up / down
    - go up and down the stack trace
  disassemble	
    - disas	
    - disassembles your program into assembly language
*/
