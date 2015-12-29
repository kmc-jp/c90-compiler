#include "code_generator.h"
#include "ast/declarations_impl.h"
#include "ast/is_method.h"
#include "ast/get_method.h"
#include "ast/ast_impl.h"

TypeVectorRef get_parameter_types_declarator(AstDeclaratorRef declarator) {
  return get_parameter_types(declarator->direct_declarator);
}

TypeVectorRef get_parameter_types_direct_declarator(AstDirectDeclaratorRef direct_declarator) {
  return get_parameter_types(direct_declarator->direct_declarator);
}

TypeVectorRef get_parameter_types_function_declarator(AstFunctionDeclaratorRef function_declarator) {
  return get_parameter_types(function_declarator->parameter_type_list);
}

TypeVectorRef get_parameter_types_parameter_type_list(AstParameterTypeListRef parameter_type_list) {
  return get_parameter_types(parameter_type_list->parameter_type_list);
}

TypeVectorRef get_parameter_types_parameter_list(AstParameterListRef parameter_list) {
  AstVectorRef parameter_vector = parameter_list->parameter_declaration_vector;
  TypeVectorRef parameter_types = TypeVectorFunc(ctor)(NULL);
  int i;
  for (i = 0; i < (int)AST_VECTOR_FUNC(size)(parameter_vector); i++) {
    AstParameterDeclarationRef parameter_declaration = 
      ast_get_parameter_declaration(AST_VECTOR_FUNC(at)(parameter_vector, i));
    if (ast_is_parameter_concrete_declaration(
          parameter_declaration->parameter_declaration)) {
      AstParameterConcreteDeclarationRef parameter_concrete_declaration =
        ast_get_parameter_concrete_declaration(parameter_declaration->parameter_declaration);
      TypeVectorFunc(push_back)(parameter_types,
          get_type(parameter_concrete_declaration->declaration_specifier_list));
    } else {
      return NULL;
    }
  }
  return parameter_types;
}

TypeVectorRef get_parameter_types(AstRef ast) {
  switch (ast->tag) {
    case AST_DECLARATOR:
      return get_parameter_types_declarator(ast_get_declarator(ast));
    case AST_DIRECT_DECLARATOR: 
      return get_parameter_types_direct_declarator(ast_get_direct_declarator(ast));
    case AST_FUNCTION_DECLARATOR:
      return get_parameter_types_function_declarator(ast_get_function_declarator(ast));
    case AST_PARAMETER_TYPE_LIST:
      return get_parameter_types_parameter_type_list(ast_get_parameter_type_list(ast));
    case AST_PARAMETER_LIST:
      return get_parameter_types_parameter_list(ast_get_parameter_list(ast));
    default: 
      return NULL;
  }
}
