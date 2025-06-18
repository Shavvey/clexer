#ifndef INCLUDE_SRC_PARSER_H_
#define INCLUDE_SRC_PARSER_H_
#include <stdio.h>
// TYPE DECLARATIONS
typedef struct _Rule {
  const char* file_content;
  const char* token_name;
} Rule;

typedef struct _TokenMap {
  const unsigned int count;
  const Rule *rules;
} TokenMap;

// API
// NOTE: right now, I woudl like to use a yaml file to generate the token we are using
TokenMap gen_rules(FILE* yaml);
#endif  // INCLUDE_SRC_PARSER_H_
