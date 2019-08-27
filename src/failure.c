#include <stdio.h>
#include <stdlib.h>

void exit_with_message(const char* message) {
    fprintf(stderr, "%s\n", message);
    exit(-1);
}
