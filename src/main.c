#include <stdio.h>
#include <stdlib.h>
#include "cli.h"

int main(int argc, const char** args) {
  if (!is_cli_args_size_valid(argc)) {
    fprintf(stderr, "emoji-committer expects exactly one argument, the Github username\n");
    exit(-1);
  }

  const char* github_username = get_github_username(args);

  printf("github_username: %s\n", github_username);
}
