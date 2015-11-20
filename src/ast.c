#include "ast.h"

DEFINE_VECTOR(AST)
void AST_ctor(AST* value) {
  *value = bad_ast();
}
void AST_dtor(AST* value) {
  UNUSED(value);
}
void AST_copy(AST* dst, const AST* src) {
  *dst = *src;
}

AST bad_ast(void) {
  AST bad;
  bad.tag = ASTTAG_ENUM_END;
  bad.ast.dummy = NULL;
  return bad;
}
