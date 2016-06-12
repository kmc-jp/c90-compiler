#include "generate.h"
#include <assert.h>
#include "ast/ast_impl.h"

void generate_code(AstRef ast) {
  assert(ast);
  switch (ast->tag) {
    default:
      fprintf(stderr, "Unimplemented: %d\n", ast->tag);
      break;
  }
}
