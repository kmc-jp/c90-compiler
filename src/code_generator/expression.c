#include "code_generator.h"
#include "variable_set.h"
#include "ast/expressions_impl.h"
#include "ast/is_method.h"
#include "ast/get_method.h"
#include "ast/ast_impl.h"

LLVMValueRef build_expression_expression(
    LLVMModuleRef module, LLVMBuilderRef builder, VariableSetRef variable_set,
    AstExpressionRef expression) {
  return build_expression(module, builder, variable_set, expression->expression);
}

LLVMValueRef build_expression_comma_expression(
    LLVMModuleRef module, LLVMBuilderRef builder, VariableSetRef variable_set,
    AstCommaExpressionRef comma_expression) {
  build_expression(module, builder, variable_set, comma_expression->expression);
  return build_expression(module, builder, variable_set, comma_expression->expression);
}

LLVMValueRef build_expression_assignment_expression(
    LLVMModuleRef module, LLVMBuilderRef builder, VariableSetRef variable_set,
    AstAssignmentExpressionRef expression) {
  return build_expression(module, builder, variable_set, expression->expression);
}

LLVMValueRef build_expression_basic_assignment_expression(
    LLVMModuleRef module, LLVMBuilderRef builder, VariableSetRef variable_set,
    AstBasicAssignmentExpressionRef expression) {
  LLVMValueRef rhs = build_expression(module, builder, variable_set, expression->assignment);
  return LLVMBuildStore(builder, rhs, get_variable(variable_set, expression->unary)->value);
}

LLVMValueRef build_expression(
    LLVMModuleRef module, LLVMBuilderRef builder, VariableSetRef variable_set, AstRef ast) {
  switch (ast->tag) {
    case AST_EXPRESSION:
      return build_expression_expression(module, builder, variable_set, ast_get_expression(ast));
    case AST_COMMA_EXPRESSION:
      return build_expression_comma_expression(module, builder, variable_set, ast_get_comma_expression(ast));
    case AST_ASSIGNMENT_EXPRESSION:
      return build_expression_assignment_expression(module, builder, variable_set, ast_get_assignment_expression(ast));
    case AST_BASIC_ASSIGNMENT_EXPRESSION:
      return build_expression_basic_assignment_expression(module, builder, variable_set, ast_get_basic_assignment_expression(ast));
    case AST_CONDITIONAL_EXPRESSION:;
    default:;
  }
  return NULL;
}
