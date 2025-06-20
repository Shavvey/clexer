#include "common.h"

// strip newline by replacing it with terminator
// NOTE: this assumes newline is at the end of the string
void strip_newline(char *str) {
  while (*str != '\n' && *str != '\0') {
    ++str;
  }
  // replace w/ null terminator
  *str = '\0';
}

// NOTE: this function doesn't close the file
unsigned int get_num_lines(FILE *file) {
  unsigned int lcount = 0;
  while (!feof(file)) {
    char c = fgetc(file);
    if (c == '\n') {
      ++lcount;
    }
  }
  rewind(file);
  return lcount;
}
