#include "variable_set.h"
#include <string.h>
#include "vector_impl.h"
#include "ast/get_method.h"
#include "ast/lexical_elements_impl.h"
#include "ast/expressions_impl.h"
#include "ast/ast_impl.h"
#include "stdstring.h"

LLVMValueRef get_variable_identifier(
    ValueVectorRef variable_set, AstIdentifierRef name) {
  AstTokenRef name_str = ast_get_token(name->token);
  LLVMValueRef *itr;
  LLVMValueRef *begin = ValueVectorFunc(begin)(variable_set);
  LLVMValueRef *end = ValueVectorFunc(end)(variable_set);
  for (itr = begin; itr != end; itr++) {
    if (strcmp(LLVMGetValueName(*itr), string_data(name_str)) == 0)
      return *itr;
  }
  return NULL;
}

LLVMValueRef get_variable_unary_expression(
    ValueVectorRef variable_set, AstUnaryExpressionRef unary) {
  return get_variable(variable_set, unary->unary);
}

LLVMValueRef get_variable_postfix_expression(
    ValueVectorRef variable_set, AstPostfixExpressionRef postfix) {
  return get_variable(variable_set, postfix->postfix);
}

LLVMValueRef get_variable(ValueVectorRef variable_set, AstRef ast) {
  switch (ast->tag) {
    case AST_UNARY_EXPRESSION:
      return get_variable_unary_expression(variable_set, ast_get_unary_expression(ast));
    case AST_POSTFIX_EXPRESSION:
      return get_variable_postfix_expression(variable_set, ast_get_postfix_expression(ast));
    case AST_IDENTIFIER:
      return get_variable_identifier(variable_set, ast_get_identifier(ast));
    default:;
  }
  return NULL;
}
