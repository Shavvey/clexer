#include "lexer.h"
#include "parser.h"
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

TokenList tokenize(const char *text, Lexer *l) {
  // generate the tokens here... it will come to me any minute
  return l->tokens;
}
