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
  if (file == NULL) return -1;
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

FileContents drain_file(const char *file_name) {
  FileContents fc = {
      .capacity = 10, .size = 0, .items = (char *)malloc(sizeof(char) * 10)};
  const int LINE_BUF_SZ = 1 << 8;
  char lbuffer[LINE_BUF_SZ];
  FILE *file = fopen(file_name, "r");
  if (file == NULL) {
    eprintf("[ERROR]: Could not open file!");
    fclose(file);
    exit(EXIT_FAILURE);
  }

  while (fgets(lbuffer, LINE_BUF_SZ, file) != NULL) {
    char *line = lbuffer;
    while (*line != '\0') {
      // printf("%c", *line);
      alist_append(&fc, *line);
      line++;
    }
  }
  return fc;
}
