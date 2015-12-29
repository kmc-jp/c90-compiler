#include "code_generator.h"
#include "ast/expressions_impl.h"
#include "ast/is_method.h"
#include "ast/get_method.h"
#include "ast/ast_impl.h"

LLVMValueRef build_expression_expression(
    LLVMModuleRef module, LLVMBuilderRef builder,
    AstExpressionRef expression) {
  return build_expression(module, builder, expression->expression);
}

LLVMValueRef build_expression_comma_expression(
    LLVMModuleRef module, LLVMBuilderRef builder,
    AstCommaExpressionRef comma_expression) {
  build_expression(module, builder, comma_expression->expression);
  return build_expression(module, builder, comma_expression->expression);
}

LLVMValueRef build_expression_assignment_expression(
    LLVMModuleRef module, LLVMBuilderRef builder,
    AstAssignmentExpressionRef expression) {
  return build_expression(module, builder, expression->expression);
}

LLVMValueRef get_value(AstRef);

LLVMValueRef build_expression_basic_assignment_expression(
    LLVMModuleRef module, LLVMBuilderRef builder,
    AstBasicAssignmentExpressionRef expression) {
  LLVMValueRef rhs = build_expression(module, builder, expression->assignment);
  return LLVMBuildStore(builder, rhs, get_value(expression->unary));
}

LLVMValueRef build_expression(
    LLVMModuleRef module, LLVMBuilderRef builder, AstRef ast) {
  switch (ast->tag) {
    case AST_EXPRESSION:
      return build_expression_expression(module, builder, ast_get_expression(ast));
    case AST_COMMA_EXPRESSION:
      return build_expression_comma_expression(module, builder, ast_get_comma_expression(ast));
    case AST_ASSIGNMENT_EXPRESSION:
      return build_expression_assignment_expression(module, builder, ast_get_assignment_expression(ast));
    case AST_BASIC_ASSIGNMENT_EXPRESSION:
      return build_expression_basic_assignment_expression(module, builder, ast_get_basic_assignment_expression(ast));
    case AST_CONDITIONAL_EXPRESSION:;
    default:;
  }
  return NULL;
}
