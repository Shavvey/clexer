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

  // alloc token name and regex into contiguous slice of mem
  /* rule contains =>
      - tname at [0, tcount + 1] (1 for null term)
      - regex at [tcount + 1 + 1, tcount + rcount + 2] */
  char *rule = (char *)malloc(sizeof(char) * (rcount + 1 + tcount + 1));
  tname = rule;
  regex = rule + tcount + 1 + 1;
  // copy token name and regex
  strncpy(tname, token_start, tcount);
  strncpy(regex, regex_start, rcount);
  // explicitly null terminate (just in case)
  tname[tcount + 1] = '\0';
  regex[rcount + 1] = '\0';
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
  printf("Number of lines => %u\n", lcount);

  if (config_file == NULL) {
    eprintf("[ERROR]: Config file is undefined!\n");
    exit(EXIT_FAILURE);
  }

  // parse and return token map
  TokenMap tk = new_token_map(lcount);

  // use fget to return each line up to the buffer size
  while (fgets(buffer, BUFFER_LEN, config_file)) {
    printf("Buffer => %s", buffer);
    Rule r = parse_rule(buffer);
    alist_append(&tk, r);
  }
  // close out of file
  fclose(config_file);
  print_tmap(&tk);
  return tk;
}

void print_rule(Rule *rule) {
  printf("Token name: %s\n", rule->tname);
  printf("Regex %s\n", rule->regex);
}

void print_tmap(TokenMap *tk) {
  for (int i = 0; i < tk->size; i++) {
    Rule r = tk->items[i];
    print_rule(&r);
  }
}
