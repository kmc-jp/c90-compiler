#include "code_generator/generate.h"
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "ast/ast_impl.h"

void generate_code(AstRef ast) {
  assert(ast);
  switch (ast->tag) {
    default:
      error("Unimplemented: %d\n", ast->tag);
      break;
  }
}

void error(const char* message, ...) {
  va_list args;
  va_start(args, message);
  vfprintf(stderr, message, args);
  va_end(args);
  fprintf(stderr, "\n");
  exit(EXIT_FAILURE);
}
