#include <stdio.h>
#include "parser.tab.h"
#include "sexpr_pool.h"
#include "utility.h"

int main(int argc, char *argv[]) {
  if (1 < argc) {
    FILE* fp = fopen(argv[1], "r");
    if (fp) {
      sexpr_initialize_pool();
      parse(fp);
      sexpr_finalize_pool();
      fclose(fp);
    }
  }
  return 0;
}
