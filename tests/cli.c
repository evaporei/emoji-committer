#include <stdbool.h>
#include "minctest.h"
#include "../src/cli.h"

void test_is_cli_args_size_valid_with_valid_size() {
  lok(is_cli_args_size_valid(2));
}

void test_is_cli_args_size_valid_with_invalid_size() {
  lok(!is_cli_args_size_valid(6));
}

void test_get_github_username_with_two_sized_list() {
  const char* args[] = {"emoji-committer", "otaviopace"};
  lok(!strcmp(get_github_username(args), "otaviopace"));
}

void cli_tests() {
  test_is_cli_args_size_valid_with_valid_size();
  test_is_cli_args_size_valid_with_invalid_size();
  test_get_github_username_with_two_sized_list();
}
