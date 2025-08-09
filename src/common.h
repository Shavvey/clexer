#ifndef INCLUDE_SRC_COMMON_H_
#define INCLUDE_SRC_COMMON_H_
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#define eprintf(...) do { fprintf(stderr, __VA_ARGS__); }while(0)
#define UNIMPLEMENTED(...) \
do {\
  printf("%s:%d UNIMPLEMENTED %s", __FILE__, __LINE__, __VA_ARGS__);\
  exit(1);\
}while(0)

#define AL_RESIZE_INC 1 << 3

#define alist_last(al) (al)->items[(al)->size-1]

#define alist_append(al, item) do {                                          \
  if ((al)->capacity - (al)->size == 0) {                                    \
    (al)->capacity += AL_RESIZE_INC;                                         \
    (al)->items = realloc((al)->items, (al)->capacity*sizeof(*(al)->items)); \
    assert((al)->items != NULL && "[ERROR]: Array list alloc failed!");      \
  }                                                                          \
  (al)->items[(al)->size++] = (item);                                        \
}while(0)

#define alist_free(al) do {   \
 (al)->size = 0;              \
 (al)->capacity = 0;          \
 free((al)->items);           \
}while(0)

//TYPE DECLARATIONS
typedef struct _FileContents {
  size_t capacity;
  size_t size;
  char *items;
} FileContents;

// common string manip functions
void strip_newline(char *str);
unsigned int get_num_lines(FILE *file);
FileContents drain_file(const char* file_name);
#endif  // INCLUDE_SRC_COMMON_H_
