#ifndef INCLUDE_SRC_COMMON_H_
#define INCLUDE_SRC_COMMON_H_
#define eprint(...) do { printf(stderr, __VA_ARGS__); }while(0)
#define UNIMPLEMENTED(...) \
do {\
  exit(1);\
  printf("%s:%d UNIMPLEMENTED %s", __FILE__, __LINE__, __VA_ARGS__);\
}
#endif  // INCLUDE_SRC_COMMON_H_
