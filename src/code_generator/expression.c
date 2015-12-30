#include "code_generator.h"
#include "variable_set.h"
#include "ast/lexical_elements_impl.h"
#include "ast/expressions_impl.h"
#include "ast/is_method.h"
#include "ast/get_method.h"
#include "ast/ast_impl.h"

LLVMValueRef build_expression_expression(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    AstExpressionRef expression) {
  return build_expression(module, builder, variable_set, expression->expression);
}

LLVMValueRef build_expression_comma_expression(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    AstCommaExpressionRef comma_expression) {
  build_expression(module, builder, variable_set, comma_expression->expression);
  return build_expression(module, builder, variable_set, comma_expression->expression);
}

LLVMValueRef build_expression_assignment_expression(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    AstAssignmentExpressionRef expression) {
  return build_expression(module, builder, variable_set, expression->expression);
}

LLVMValueRef build_expression_basic_assignment_expression(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    AstBasicAssignmentExpressionRef expression) {
  LLVMValueRef rhs = build_expression(module, builder, variable_set, expression->assignment);
  return LLVMBuildStore(builder, rhs, get_variable(variable_set, expression->unary));
}

LLVMValueRef build_expression_conditional_expression(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    AstConditionalExpressionRef expression) {
  return build_expression(module, builder, variable_set, expression->expression);
}

LLVMValueRef build_expression_logical_or_expression(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    AstLogicalOrExpressionRef expression) {
  return build_expression(module, builder, variable_set, expression->expression);
}

LLVMValueRef build_expression_logical_and_expression(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    AstLogicalAndExpressionRef expression) {
  return build_expression(module, builder, variable_set, expression->expression);
}

LLVMValueRef build_expression_bitwise_or_expression(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    AstBitwiseOrExpressionRef expression) {
  return build_expression(module, builder, variable_set, expression->expression);
}

LLVMValueRef build_expression_bitwise_xor_expression(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    AstBitwiseXorExpressionRef expression) {
  return build_expression(module, builder, variable_set, expression->expression);
}

LLVMValueRef build_expression_bitwise_and_expression(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    AstBitwiseAndExpressionRef expression) {
  return build_expression(module, builder, variable_set, expression->expression);
}

LLVMValueRef build_expression_equality_expression(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    AstEqualityExpressionRef expression) {
  return build_expression(module, builder, variable_set, expression->expression);
}

LLVMValueRef build_expression_relarional_expression(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    AstRelationalExpressionRef expression) {
  return build_expression(module, builder, variable_set, expression->expression);
}

LLVMValueRef build_expression_shift_expression(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    AstShiftExpressionRef expression) {
  return build_expression(module, builder, variable_set, expression->expression);
}

LLVMValueRef build_expression_additive_expression(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    AstAdditiveExpressionRef expression) {
  return build_expression(module, builder, variable_set, expression->expression);
}

LLVMValueRef build_expression_multiplicative_expression(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    AstMultiplicativeExpressionRef expression) {
  return build_expression(module, builder, variable_set, expression->expression);
}

LLVMValueRef build_expression_cast_expression(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    AstCastExpressionRef cast) {
  return build_expression(module, builder, variable_set, cast->cast);
}

LLVMValueRef build_expression_unary_expression(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    AstUnaryExpressionRef unary) {
  return build_expression(module, builder, variable_set, unary->unary);
}

LLVMValueRef build_expression_function_call_expression(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    AstFunctionCallExpressionRef function_call) {
  AstTokenRef function_name = get_name(function_call->function);
  LLVMValueRef function = LLVMGetNamedFunction(module, string_data(function_name));
  LLVMTypeRef function_type = LLVMGetElementType(LLVMTypeOf(function));
  int parameter_count = LLVMCountParamTypes(function_type);
  ValueVectorRef argument_vec =
    get_arguments(
        variable_set,
        ast_get_argument_expression_list(function_call->argument_list));
  int argument_count = ValueVectorFunc(size)(argument_vec);
  if (parameter_count != argument_count) return NULL;
  return LLVMBuildCall(builder, function, ValueVectorFunc(data)(argument_vec),
      ValueVectorFunc(size)(argument_vec), string_data(function_name));
}

LLVMValueRef build_expression_postfix_expression(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    AstPostfixExpressionRef postfix) {
  return build_expression(module, builder, variable_set, postfix->postfix);
}

LLVMValueRef build_expression_primary_expression(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    AstPrimaryExpressionRef primary) {
  return build_expression(module, builder, variable_set, primary->primary_expression);
}

LLVMValueRef build_expression_constant(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    AstConstantRef constant) {
  return build_expression(module, builder, variable_set, constant->constant);
}

LLVMValueRef build_expression_integer_constant(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    AstIntegerConstantRef constant) {
  return LLVMConstIntOfString(
      LLVMInt32Type(), string_data(ast_get_token(constant->token)), 10);
}

LLVMValueRef build_expression_identifier(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    AstIdentifierRef identifier) {
  return get_variable_identifier(variable_set, identifier);
}

LLVMValueRef build_expression(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set, AstRef ast) {
  switch (ast->tag) {
    case AST_EXPRESSION:
      return build_expression_expression(module, builder, variable_set, ast_get_expression(ast));
    case AST_COMMA_EXPRESSION:
      return build_expression_comma_expression(module, builder, variable_set, ast_get_comma_expression(ast));
    case AST_ASSIGNMENT_EXPRESSION:
      return build_expression_assignment_expression(module, builder, variable_set, ast_get_assignment_expression(ast));
    case AST_BASIC_ASSIGNMENT_EXPRESSION:
      return build_expression_basic_assignment_expression(module, builder, variable_set, ast_get_basic_assignment_expression(ast));
    case AST_CONDITIONAL_EXPRESSION:
      return build_expression_conditional_expression(module, builder, variable_set, ast_get_conditional_expression(ast));
    case AST_LOGICAL_OR_EXPRESSION:
      return build_expression_logical_or_expression(module, builder, variable_set, ast_get_logical_or_expression(ast));
    case AST_LOGICAL_AND_EXPRESSION:
      return build_expression_logical_and_expression(module, builder, variable_set, ast_get_logical_and_expression(ast));
    case AST_BITWISE_OR_EXPRESSION:
      return build_expression_bitwise_or_expression(module, builder, variable_set, ast_get_bitwise_or_expression(ast));
    case AST_BITWISE_XOR_EXPRESSION:
      return build_expression_bitwise_xor_expression(module, builder, variable_set, ast_get_bitwise_xor_expression(ast));
    case AST_BITWISE_AND_EXPRESSION:
      return build_expression_bitwise_and_expression(module, builder, variable_set, ast_get_bitwise_and_expression(ast));
    case AST_EQUALITY_EXPRESSION:
      return build_expression_equality_expression(module, builder, variable_set, ast_get_equality_expression(ast));
    case AST_RELATIONAL_EXPRESSION:
      return build_expression_relarional_expression(module, builder, variable_set, ast_get_relational_expression(ast));
    case AST_SHIFT_EXPRESSION:
      return build_expression_shift_expression(module, builder, variable_set, ast_get_shift_expression(ast));
    case AST_ADDITIVE_EXPRESSION:
      return build_expression_additive_expression(module, builder, variable_set, ast_get_additive_expression(ast));
    case AST_MULTIPLICATIVE_EXPRESSION:
      return build_expression_multiplicative_expression(module, builder, variable_set, ast_get_multiplicative_expression(ast));
    case AST_CAST_EXPRESSION:
      return build_expression_cast_expression(module, builder, variable_set, ast_get_cast_expression(ast));
    case AST_UNARY_EXPRESSION:
      return build_expression_unary_expression(module, builder, variable_set, ast_get_unary_expression(ast));
    case AST_POSTFIX_EXPRESSION:
      return build_expression_postfix_expression(module, builder, variable_set, ast_get_postfix_expression(ast));
    case AST_FUNCTION_CALL_EXPRESSION:
      return build_expression_function_call_expression(module, builder, variable_set, ast_get_function_call_expression(ast));
    case AST_PRIMARY_EXPRESSION:
      return build_expression_primary_expression(module, builder, variable_set, ast_get_primary_expression(ast));
    case AST_CONSTANT:
      return build_expression_constant(module, builder, variable_set, ast_get_constant(ast));
    case AST_INTEGER_CONSTANT:
      return build_expression_integer_constant(module, builder, variable_set, ast_get_integer_constant(ast));
    case AST_IDENTIFIER:
      return build_expression_identifier(module, builder, variable_set, ast_get_identifier(ast));
    default:;
  }
  return NULL;
}
