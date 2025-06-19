#include "parser.h"
#include "common.h"
#include <stdlib.h>
#include <string.h>

Rule parse_rule(const char *line) {
  int tcount;
  int rcount;

  char *tname;
  char *regex;

  // chop out whitespace
  while (*line == ' ')
    line++;

  const char *token_start = line;

  while (*(++line) != ':') {
    if (*line == '\0') {
      eprintf("[ERROR]: Could not parse rule! Line expectedly ended");
      exit(EXIT_FAILURE);
    }
    tcount++;
  }

  // reset char count and move passed ':'
  ++line;

  // chop out whitespace, again
  while (*line == ' ')
    ++line;

  const char *regex_start = line;

  while (*(++line) != '\0') {
    ++rcount;
  }

  // alloc token name and regex into contiguous series of bytes
  char *rule = (char *)malloc(sizeof(char) * (rcount + 1 + tcount + 1));
  tname = rule;
  regex = rule + tcount + 1;
  // copy token name and regex
  strncpy(tname, token_start, tcount);
  strncpy(regex, regex_start, rcount);
  // construct new rule
  Rule new_rule = {.tname = tname, .regex = regex};
  return new_rule;
}

TokenMap gen_rules(const char *fname) {
  // NOTE: we don't expect each key-value pair to be longer
  // than this length (we can check this assumption w/ asserts if needed)
  const int BUFFER_LEN = 255;
  char buffer[BUFFER_LEN];
  FILE *config_file = fopen(fname, "r");

  if (config_file == NULL) {
    eprintf("[ERROR]: Config file is undefined!\n");
    exit(EXIT_FAILURE);
  }

  // use fget to return each line up to the buffer size
  while (fgets(buffer, BUFFER_LEN, config_file)) {
    printf("Buffer => %s", buffer);
    Rule r = parse_rule(buffer);
  }
  // close out of file
  fclose(config_file);

  // parse and return token map
  TokenMap tk = {0};
  return tk;
}
