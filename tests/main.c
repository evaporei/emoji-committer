#include "minctest.h"
#include "list.h"

int main() {
  lrun("cli_tests", cli_tests);
  lresults();
  return lfails != 0;
}
