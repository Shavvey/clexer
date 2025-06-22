#include "parser.h"
#include "regex/re.h"

int main(int argc, char *argv[]) {
  TokenMap tm = gen_rules("example-map.conf");
  int match_length = 0;
  int match_idx = re_match("[0-9]*", "AA", &match_length);
  printf("match_idx: %d\nmatch_length: %d\n", match_idx, match_length);
}
