
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

// function pointers
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

void qsort(void *base, size_t nelm, size_t size, int (*compar)(const void *, cosnt void *)); 

// each one of the void* points to an elem in the array, the int it returns indicates result of comparison
int compar_str(cosnt void *s1, const void *s2) {
  return strcmp(*(char **)s1, *(char **) s2);
}

/*
Valgrind
  Memory leak
    - didn't free memory you previously allocated
  Memory access
    - read or write memory you don'thave access to
*/
