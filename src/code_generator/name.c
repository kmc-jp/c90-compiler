#include "code_generator.h"
#include "stdstring.h"
#include "ast/lexical_elements_impl.h"
#include "ast/expressions_impl.h"
#include "ast/is_method.h"
#include "ast/get_method.h"
#include "ast/ast_impl.h"

AstTokenRef get_name_identifier(AstIdentifierRef identifier) {
  return ast_get_token(identifier->token);
}

AstTokenRef get_name_primary_expression(AstPrimaryExpressionRef primary) {
  return get_name(primary->primary_expression);
}

AstTokenRef get_name_postfix_expression(AstPostfixExpressionRef postfix) {
  return get_name(postfix->postfix);
}

AstTokenRef get_name_unary_expression(AstUnaryExpressionRef unary) {
  return get_name(unary->unary);
}

AstTokenRef get_name(AstRef ast) {
  switch (ast->tag) {
    case AST_IDENTIFIER:
      return get_name_identifier(ast_get_identifier(ast));
    case AST_PRIMARY_EXPRESSION:
      return get_name_primary_expression(ast_get_primary_expression(ast));
    case AST_POSTFIX_EXPRESSION:
      return get_name_postfix_expression(ast_get_postfix_expression(ast));
    case AST_UNARY_EXPRESSION:
      return get_name_unary_expression(ast_get_unary_expression(ast));
    default:
      return NULL;
  }
}
