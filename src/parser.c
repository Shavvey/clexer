#include "parser.h"
#include "common.h"
#include <stdlib.h>
#include <string.h>

Rule parse_rule(const char *line) {
  int tcount = 1;
  int rcount = 1;

  // chop out whitespace
  while (*line == ' ')
    line++;

  const char *token_start = line;

  while (*(++line) != ':') {
    if (*line == '\0') {
      eprintf(
          "[ERROR]: Could not parse rule because the line unexpectedly ended!");
      exit(EXIT_FAILURE);
    }
    if (*line != ' ')
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
  // TODO: throw this into a big memory slice, for caching reasons
  char *tname = (char *)malloc(sizeof(char) * tcount);
  char *regex = (char *)malloc(sizeof(char) * rcount);
  // copy token name and regex
  strncpy(tname, token_start, tcount);
  strncpy(regex, regex_start, rcount);
  strip_newline(regex);
  // construct new rule
  Rule r = {.tname = tname, .regex = regex};
  return r;
}

static TokenMap new_token_map(size_t capacity) {
  TokenMap tm = {.size = 0,
                 .capacity = capacity,
                 .items = (Rule *)malloc(sizeof(Rule) * capacity)};
  return tm;
}

TokenMap gen_rules(const char *fname) {
  // NOTE: we don't expect each key-value pair to be longer
  // than this length (we can check this assumption w/ asserts if needed)
  const int BUFFER_LEN = 1 << 8;
  char buffer[BUFFER_LEN];
  FILE *config_file = fopen(fname, "r");
  const unsigned int lcount = get_num_lines(config_file);

  if (config_file == NULL) {
    eprintf("[ERROR]: Config file is undefined!\n");
    fclose(config_file);
    exit(EXIT_FAILURE);
  }

  // parse and return token map
  TokenMap tm = new_token_map(lcount);

  // use fget to return each line up to the buffer size
  while (fgets(buffer, BUFFER_LEN, config_file)) {
    // parse rule and append to token map
    Rule r = parse_rule(buffer);
    alist_append(&tm, r);
  }
  // close out of file
  fclose(config_file);
  return tm;
}

void print_rule(Rule *rule) {
  printf("Token name: %s\n", rule->tname);
  printf("Regex %s\n", rule->regex);
}

void print_tmap(TokenMap *tm) {
  for (int i = 0; i < tm->size; i++) {
    Rule r = tm->items[i];
    print_rule(&r);
  }
}
