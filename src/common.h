#ifndef INCLUDE_SRC_COMMON_H_
#define INCLUDE_SRC_COMMON_H_
#include <stdlib.h>
#include <stdio.h>
#define eprintf(...) do { fprintf(stderr, __VA_ARGS__); }while(0)
#define UNIMPLEMENTED(...) \
do {\
  printf("%s:%d UNIMPLEMENTED %s", __FILE__, __LINE__, __VA_ARGS__);\
  exit(1);\
}while(0)

#define AL_RESIZE_INC 1 << 3

#define alist_last(al) (assert((al)-> size > 0 && "[ERROR]: No room in array_list!"),\
(al)->items[(da)->count-1]) 

#define alist_append(al, item) do {                                         \
  if ((al)->capacity - (al)->size == 0) {                                   \
    (al)->capacity += AL_RESIZE_INC;                                        \
    (al)->items = realloc((al)->items, (da)->capcity*sizeof(*(al)->items)); \
    assert((al)->items != NULL && "[ERROR]: Array list alloc failed!");     \
  }                                                                         \
  (al)->items[(al)->size++] = (item);                                       \
}while(0)


// common string manip functions
void strip_newline(char *str);
unsigned int get_num_lines(FILE *file);
#endif  // INCLUDE_SRC_COMMON_H_
