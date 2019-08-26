#include <stdio.h>
#include <stdlib.h>

const char* parse_cli_args(int argc, const char** args) {
  if (argc != 2) {
    fprintf(stderr, "emoji-committer expects exactly one argument, the Github username\n");
    exit(-1);
  }

  return args[1];
}
