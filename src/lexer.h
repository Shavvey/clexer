#ifndef INCLUDE_SRC_LEXER_H_
#define INCLUDE_SRC_LEXER_H_

#include <stddef.h>
#include <stdio.h>

// DEPS
#include "parser.h"
#include "regex/re.h"

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
} Lexer;

typedef struct _Match {
  int idx;
  int length;
} Match;

typedef struct _MatchSet {
  size_t capacity;
  size_t size;
  Match *items; 
} MatchSet;


// API
TokenList tokenize(Lexer *l);
Token get_first(TokenList *tlist);
void print_tokens(TokenList *tlist);
Lexer new_lexer(const char* text, const TokenMap *tm);

#endif  // INCLUDE_SRC_LEXER_H_
