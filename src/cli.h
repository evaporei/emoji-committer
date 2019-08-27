#ifndef __CLI_H__
#define __CLI_H__

#include <stdbool.h>

bool is_cli_args_size_valid(int args_size);

const char* get_github_username(const char** args);

#endif /* __CLI_H__ */
