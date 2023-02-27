/*
Arrays
  T A[N] allocates sizeof(T) * N bytes, gives us an identifier that we can use as a pointer (but not a pointer) with a value of the strating location xA

Structs
  The C struct declaration is used to group objects of different types into a single unit.
  Each "field" is referenced by a name, and can be accessed using dot (.) or (if there is a pointer to the struct) arrow (->) notation.
  Structures are kept in contiguous memory
  To access the fields, the compiler generates code that adds the field offset to the address of the structure.

Data alignment
  Computer systems often put restrictions on the allowable addresses for primitive data types, 
  requiring that the address for some objects must be a multiple of some value K (normally 2, 4, or 8).
*/
