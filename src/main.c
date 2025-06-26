#include "lexer.h"

int main(int argc, char *argv[]) {
  const TokenMap tm = gen_rules("example-map.conf");
  Lexer l = new_lexer("int main() {}", &tm);
  TokenList tl = tokenize(&l);
  print_tokens(&tl);
}
