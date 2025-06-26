#include "lexer.h"
#include "common.h"
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
  // NOTE: this is really inefficient! but the re_compile forces us to deep copy the results,
  // which I DO NOT want to do, so for now we compile and exec each lexer loop (which is very bad)
  Match m = {0};
  for (int i = 0; i < tm->size; i++) {
    Rule r = tm->items[i];
    m.idx = re_match(r.regex, text, &m.length);
    alist_append(ms, m);
  } 
}

int get_max_idx(MatchSet *ms) {
  int idx = -1;
  Match max = ms->items[0];
  for (int i = 0; i < ms->size; i++) {
    Match m = ms->items[i]; 
    if (m.idx == 0 && max.length < m.length) {
      max = m;
      idx = i;
    }
  }
  return idx;
}

Token munch(Lexer *l, Rule r) {

}


TokenList tokenize(Lexer *l) {
  chop_left(l);
  const TokenMap tm = l->map;
  MatchSet ms = new_matches(tm.capacity);
  get_matches(&ms, l->content + l->cursor, &tm);
  print_matchset(&ms);
  int idx = get_max_idx(&ms);
  printf("Max match result is at: %d\n", idx);
  return l->tokens;
}
