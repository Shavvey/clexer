#include "lexer.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
  const TokenMap tm = gen_rules("example-map.conf");
  TokenList tl = tokenize_file("example.txt", &tm);
  print_tokens(&tl);
  return EXIT_SUCCESS;
}
