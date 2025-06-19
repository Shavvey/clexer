#ifndef INCLUDE_SRC_COMMON_H_
#define INCLUDE_SRC_COMMON_H_
#define eprintf(...) do { fprintf(stderr, __VA_ARGS__); }while(0)
#define UNIMPLEMENTED(...) \
do {\
  printf("%s:%d UNIMPLEMENTED %s", __FILE__, __LINE__, __VA_ARGS__);\
  exit(1);\
}
#endif  // INCLUDE_SRC_COMMON_H_
