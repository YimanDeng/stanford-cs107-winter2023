
/*
1. C pointers
  - just a number indicating memory addresses. Myth machines pointers are 8-byte long
*/
int x = 7;
int *xptr = &x; // pointer to x
printf("address of x: &p\n", xptr);
printf("x via dereferencing xptr: %d\n", *xptr);
