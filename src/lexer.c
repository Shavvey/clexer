#include "lexer.h"
#include "common.h"
#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void chop_left(Lexer *l) {
  // cut out white space and newlines
  char c = l->content[l->cursor];
  while (c == '\n' || c == ' ' || c == '\r') {
    l->cursor += 1;
    c = l->content[l->cursor];
  }
}
void print_token(Token t) {
    printf("TOKEN: %s(%s)\n", t.kind, t.content);
}

void print_tokens(TokenList *tlist) {
  for (int i = 0; i < tlist->size; i++) {
    Token t = tlist->items[i];
    print_token(t);
  }
}

static TokenList new_token_list(size_t capacity) {
  TokenList tl = {.capacity = capacity,
                  .size = 0,
                  .items = (Token *)malloc(sizeof(Token) * capacity)};
  return tl;
}

Lexer new_lexer(const char *text, const TokenMap *tm) {
  Lexer l = {.content = text, // text that we would like to tokenize
             .map = *tm,      // use the token map passed into lexer
             .tokens = new_token_list(
                 10), // NOTE: revise later to make a better guess at capacity
             .cursor = 0};
  return l;
}

MatchSet new_matches(size_t capacity) {
  MatchSet ms = {.capacity = capacity,
                 .size = 0,
                 .items = (Match *)malloc(sizeof(Match) * capacity)};
  return ms;
}

static void print_match(Match *m) {
  printf("Match idx: %d\n", m->idx);
  printf("Match length: %d\n", m->length);
}

void print_matchset(const MatchSet *ms) {
  for (int i = 0; i < ms->size; i++) {
    print_match(&ms->items[i]);
  }
}

void clear_matches(MatchSet *ms) {
  ms->size = 0;
  // NOTE: we could zero out array list here, but why bother?
}

void get_matches(MatchSet *ms, const char *text, const TokenMap *tm) {
  // NOTE: this is really inefficient! but the re_compile forces us to deep copy
  // the results, which I DO NOT want to do, so for now we compile and exec each
  // lexer loop (which is very bad)
  Match m = {0};
  for (int i = 0; i < tm->size; i++) {
    Rule r = tm->items[i];
    m.idx = re_match(r.regex, text, &m.length);
    alist_append(ms, m);
  }
}

int get_max_idx(MatchSet *ms) {
  int idx = -1;
  Match max = {.idx = idx, .length = -1};
  for (int i = 0; i < ms->size; i++) {
    Match m = ms->items[i];
    if (m.idx == 0 && max.length < m.length) {
      max = m;
      idx = i;
    }
  }
  return idx;
}

static Token munch(Lexer *l, const char *tname, size_t length) {
  char *tkcontent = (char *)malloc(sizeof(char) * length + 1);
  strncpy(tkcontent, l->content + l->cursor, length);
  l->cursor += length;
  // null terminate constructed string
  tkcontent[length] = '\0';
  Token t = {.kind = tname, .content = tkcontent};
  return t;
}

static bool is_printable_ascii(char c) {
  if (c >= 33 && c <= 126) {
    return true;
  }
  return false;
}

TokenList tokenize(Lexer *l) {
  chop_left(l);
  const TokenMap tm = l->map;
  MatchSet ms = new_matches(tm.capacity);
  while (l->content[l->cursor] != '\0') {
    get_matches(&ms, l->content + l->cursor, &tm);
    int idx = get_max_idx(&ms);
    if(idx > -1) {
      Token t = munch(l, tm.items[idx].tname, ms.items[idx].length);
      alist_append(&l->tokens, t);
    } else {
      char c = l->content[l->cursor]; 
      // check to see if this is a control character, ignore if this is the case
      if (!is_printable_ascii(c)) {
        l->cursor++;
      } else {
        // TODO: some better error reporting maybe?
        eprintf("[ERROR]: Could not match content: \"%c\" at %d\n",
                c, l->cursor);
        l->cursor++;
      }
    }
    chop_left(l);
    clear_matches(&ms);
  }
  return l->tokens;
}

TokenList tokenize_file(const char *file_name, const TokenMap *tm) {
  FileContents fc = drain_file(file_name);
  Lexer l = new_lexer(fc.items, tm);
  return tokenize(&l);
}
