#include <stdbool.h>

bool is_cli_args_size_valid(int args_size) {
  return args_size == 2;
}

const char* get_github_username(const char** args) {
  return args[1];
}
