#include "variable_set.h"
#include "vector_impl.h"
#include "pool.h"
#include "ast/get_method.h"
#include "ast/lexical_elements_impl.h"
#include "ast/expressions_impl.h"
#include "ast/ast_impl.h"

VariableRef get_variable_identifier(
    VariableSetRef variable_set, AstIdentifierRef name) {
  AstTokenRef name_str = ast_get_token(name->token);
  VariableRef *itr;
  VariableRef *begin = VariableSetFunc(begin)(variable_set);
  VariableRef *end = VariableSetFunc(end)(variable_set);
  for (itr = begin; itr != end; itr++) {
    if (string_compare((*itr)->name, name_str) == 0)
      return *itr;
  }
  return NULL;
}

VariableRef get_variable_unary_expression(
    VariableSetRef variable_set, AstUnaryExpressionRef unary) {
  return get_variable(variable_set, unary->unary);
}

VariableRef get_variable_postfix_expression(
    VariableSetRef variable_set, AstPostfixExpressionRef postfix) {
  return get_variable(variable_set, postfix->postfix);
}

VariableRef get_variable(VariableSetRef variable_set, AstRef ast) {
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

void make_variable(VariableSetRef variable_set, AstTokenRef name, LLVMTypeRef type, LLVMValueRef value) {
  VariableRef variable = codegen_palloc(struct Variable);
  variable->name = name;
  variable->type = type;
  variable->value = value;
  VariableSetFunc(push_back)(variable_set, variable);
}
