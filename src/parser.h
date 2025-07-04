#ifndef INCLUDE_SRC_PARSER_H_
#define INCLUDE_SRC_PARSER_H_
#include <stdio.h>
// TYPE DECLARATIONS
typedef struct _Rule {
  const char* tname;
  const char* regex;
} Rule;

typedef struct _TokenMap {
  size_t size;
  size_t capacity;
  Rule *items;
} TokenMap;

// API
// takes in key-value pairs delimited by a colon.
// The key represents the name/kind of token, and the
// value is the regex
TokenMap gen_rules(const char *fname);
void print_rule(Rule *rule);
void print_tmap(TokenMap *tk);
#endif  // INCLUDE_SRC_PARSER_H_
