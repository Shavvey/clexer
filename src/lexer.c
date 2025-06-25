#include "lexer.h"
#include "parser.h"
#include "regex/re.h"
#include <stdlib.h>

void chop_left(Lexer *l) {
  // cut out white space chars
  while (*l->content == ' ')
    ++l->cursor;
}

static TokenList new_token_list(size_t capacity) {
  TokenList tl = {.capacity = capacity,
                  .size = 0,
                  .items = (Token *)malloc(sizeof(Token) * capacity)};
  return tl;
}

Lexer new_lexer(const char *text, const TokenMap *tm) {
  Lexer l = {
      .content = text, // text that we would like to tokenize
      .map = *tm,      // use the token map passed into lexer
      .tokens = new_token_list(
          10), // NOTE: revise later to make a better guess at capacity
  };
  return l;
}

void get_matches(MatchSet *ms, const char* text, re_t* regexes) {
   
}

void clear_matches(MatchSet *ms) {}

TokenList tokenize(Lexer *l) {
  chop_left(l);
  MatchSet ms = {0};
  re_t regexes[l->map.size];
  TokenMap tp = l->map;

  // iterate through token map and contruct regexes
  for (int i = 0; i < tp.size; i++) {
    Rule r = tp.items[i];
    print_rule(&r);
    re_t regex = re_compile(r.regex);
    regexes[i] = regex;
  } 

  return l->tokens;
}
