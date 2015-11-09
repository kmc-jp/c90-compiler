#include <stdio.h>
#include <stdlib.h>
#include "lex.yy.h"
#include "yacc_mock.h"
#include "lexer_adapter.h"

void yyin_from_file(const char *filename) {
  FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("fatal error: failed to open %s\n", filename);
    exit(EXIT_FAILURE);
  }
  yyin = fp;
}

void yyin_from_string(const char *code) {
  yy_scan_string(code);
}
