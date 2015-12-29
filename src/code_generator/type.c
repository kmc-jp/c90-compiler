#include "code_generator.h"
#include "stdstring.h"
#include "ast/is_method.h"
#include "ast/get_method.h"
#include "ast/ast_impl.h"

DEFINE_VECTOR(LLVMTypeRef)

LLVMTypeRef get_type(AstRef ast) {
  switch (ast->tag) {
    case AST_DECLARATION_SPECIFIER_LIST:
      return LLVMInt32Type();
    default:
      return NULL;
  }
}
