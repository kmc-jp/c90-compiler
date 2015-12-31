#include "code_generator.h"
#include "stdstring.h"
#include "ast/declarations_impl.h"
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

LLVMTypeRef get_type_with_type_declarator(
    LLVMTypeRef base_type, AstDeclaratorRef declarator) {
  LLVMTypeRef direct_type = get_type_with_type(base_type, declarator->direct_declarator);
  return get_type_with_type(direct_type, declarator->pointer);
}

LLVMTypeRef get_type_with_type_direct_declarator(
    LLVMTypeRef base_type, AstDirectDeclaratorRef direct_declarator) {
  return get_type_with_type(base_type, direct_declarator->direct_declarator);
}

LLVMTypeRef get_type_with_type_pointer(
    LLVMTypeRef base_type, AstPointerRef pointer) {
  if (pointer->pointer == NULL) return base_type;
  else
    return get_type_with_type(LLVMPointerType(base_type, 0), pointer->pointer);
}

LLVMTypeRef get_type_with_type_identifier(
    LLVMTypeRef base_type, AstIdentifierRef identifier) {
  UNUSED(identifier);
  return base_type;
}

LLVMTypeRef get_type_with_type(LLVMTypeRef base_type, AstRef ast) {
  switch (ast->tag) {
    case AST_DECLARATOR:
      return get_type_with_type_declarator(base_type, ast_get_declarator(ast));
    case AST_DIRECT_DECLARATOR:
      return get_type_with_type_direct_declarator(
          base_type, ast_get_direct_declarator(ast));
    case AST_POINTER:
      return get_type_with_type_pointer( base_type, ast_get_pointer(ast));
    case AST_IDENTIFIER:
      return get_type_with_type_identifier(base_type, ast_get_identifier(ast));
    default:
      return NULL;
  }
}
