#ifndef INCLUDE_SRC_LEXER_H_
#define INCLUDE_SRC_LEXER_H_

#include <stddef.h>
#include <stdio.h>

// DEPS
#include "parser.h"

// TYPE DECLARATIONS
typedef struct _Token {
  const char *kind;
  const char *content;
} Token;

typedef struct _TokenList {
  size_t capacity;
  size_t size;
  Token *tokens; 
} TokenList;

typedef struct _Lexer {
  const char* text;
  TokenList tokens;
  TokenMap map;
  unsigned int cursor;
  unsigned int bol;
} Lexer;

// API
Lexer tokenize(const char *text, unsigned int nthreads);
void print_tokens(Lexer *lexer);
TokenList make_token_list(size_t size);
Token get_first(TokenList *tlist);
Token append(TokenList *tlist);
Lexer merge(Lexer *lhs, Lexer *rhs);

#endif  // INCLUDE_SRC_LEXER_H_
