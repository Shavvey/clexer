#ifndef INCLUDE_SRC_COMMON_H_
#define INCLUDE_SRC_COMMON_H_
#include <stdlib.h>
#define eprintf(...) do { fprintf(stderr, __VA_ARGS__); }while(0)
#define UNIMPLEMENTED(...) \
do {\
  printf("%s:%d UNIMPLEMENTED %s", __FILE__, __LINE__, __VA_ARGS__);\
  exit(1);\
}while(0)

#define alist_last(al) (assert((al)-> size > 0 && "[ERROR]: No room in array_list!"),\
(al)->items[(da)->count-1]) 
#define alist_append(al) (assert((al)->capacity - (al)->size > 0 && "[ERROR]: No room in array_list!"))\

// common string manip functions
void strip_newline(char *str);
#endif  // INCLUDE_SRC_COMMON_H_
