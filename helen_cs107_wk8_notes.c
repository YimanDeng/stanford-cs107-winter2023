/*
1. Allocating memory

void *malloc(size_t size)
  return pointer to memory >= requested size
  failure returns NULL and sets errno
  
void free(void *p)
  recycle memory block
  p must be previous malloc/realloc call
  
void *realloc(void *p, size_t size)
  changes size of block p, returns pointer to block (possibly different)
  contents of new block unchanged up to min of old and new size
  If new pointer not same as old pointer, the old block is freed
  
The heap allocator must be able to service an arbitrary sequence of malloc() and free()
It must align blocks so that they satisfy all alignment requirements (e.g., 8-byte / 16 byte boundary)
The allocator cannot move allocated blocks.

Goals
  Ideally, requests should be handled in constant itme, and not degrade to linear behavior
  The allocator must try for a tight space utilization. Should try to minimize fragmentation.
  Good locality, blocks are allocated close in time and space.
  Robust, client errors should be recognized.
  Ease of implementation and maintenance. Use structs and typedef instead of having a lot of *(void **)

Design questions
- How do we track the information in a block?
- How do we organize/find free block?
- How do we pick which free block from available options?
- What do we do with excess space when allocating a block?
- How do we recycle a freed block? 

Options
- A separate list. Valgrind uses this
- Block header "implicit free list"
  info in same memory area as the payload, but precedes the payload. (What's actually used)
  Coalescing forward (can't do backward without footer)
  Have list of free blocks that we can traverse to find an appropriate fit. not really efficient
  Do not bother making a new header is the blobks free is 0.
  Finding free blocks is a linear search process. (first-fit)
  Other options like next-fit, best-fit.
- Explicit free list
  Also keep the meta data inside the heap. Have a pointer to the next and previous free block.
  A linked list implementation.
  Faster because you only have to traverse the free blocks.
*/

/*
2. Assignment tips
  Cast void* pointer to a struct pointer to make it easier to debug.
*/
