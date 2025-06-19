// strip newline by replacing it with terminator
// NOTE: this assumes newline is at the end of the string
void strip_newline(char *str) {
  while(*str != '\n' && *str != '\0') {
    ++str;
  }
  // replace w/ null terminator
  *str = '\0';
} 
