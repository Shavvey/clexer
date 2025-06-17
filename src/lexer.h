#include <stddef.h>
#include <stdio.h>

// TYPE DECLARATIONS
typedef struct _Token {
  const char *name;
  const char *val;
  unsigned int start;
  unsigned int end;
}Token;

typedef struct _TokenList {
  size_t capacity;
  size_t size;
  Token *tokens; 
}TokenList;

typedef struct _Lexer {
  TokenList tokens;
  FILE *file;
}Lexer;

// API
Lexer tokenize(FILE *file, unsigned int nthreads);
void print_tokens(Lexer *lexer);
TokenList make_token_list(size_t size);
Token get_first(TokenList *tlist);
Token append(TokenList *tlist);
Lexer merge(Lexer *lhs, Lexer *rhs);
