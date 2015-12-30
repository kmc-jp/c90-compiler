#include "code_generator.h"
#include "stdstring.h"
#include "ast/is_method.h"
#include "ast/get_method.h"
#include "ast/ast_impl.h"

LLVMTypeRef get_type_declaration_specifier_list(
    AstDeclarationSpecifierListRef declaration_specifier_list) {
  return LLVMInt32Type();
}

LLVMTypeRef get_type(AstRef ast) {
  switch (ast->tag) {
    case AST_DECLARATION_SPECIFIER_LIST:
      return get_type_declaration_specifier_list(ast_get_declaration_specifier_list(ast));
    default:
      return NULL;
  }
}
