#include <stdio.h>
#include "cli.h"
#include "failure.h"

int main(int argc, const char** args) {
  if (!is_cli_args_size_valid(argc)) {
    exit_with_message("emoji-committer expects exactly one argument, the Github username");
  }

  const char* github_username = get_github_username(args);

  printf("github_username: %s\n", github_username);
}
