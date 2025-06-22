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
  Token *items; 
} TokenList;

typedef struct _Lexer {
  const char* content;
  TokenList tokens;
  const TokenMap map;
  unsigned int cursor; // points to current line content
  unsigned int bol; // beginning of line
} Lexer;

typedef struct _Match {
  int idx;
  int lenght;
}Match;

typedef struct _MatchSet {
  size_t capacity;
  size_t size;
  Match *items; 
} MatchSet;

// API
TokenList tokenize(const char *text, Lexer *l);
void print_tokens(Lexer *lexer);
Token get_first(TokenList *tlist);
Token append(TokenList *tlist);
Lexer merge(Lexer *lhs, Lexer *rhs);
Lexer new_lexer(const char* text, const TokenMap tm);

#endif  // INCLUDE_SRC_LEXER_H_
