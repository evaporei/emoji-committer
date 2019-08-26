#include <stdio.h>
#include "cli.h"

int main(int argc, const char** args) {
  const char* github_username = parse_cli_args(argc, args);

  printf("github_username: %s\n", github_username);
}
