#include "expressions.h"
#include "expressions_impl.h"
#include "ast_impl.h"
#include "is_method.h"
#include "get_method.h"
#include "pool.h"

AstRef ast_make_primary_expression(AstRef primary_expression) {
  AstRef self = NULL;
  if (ast_is_identifier(primary_expression) ||
      ast_is_constant(primary_expression) ||
      ast_is_string_literal(primary_expression) ||
      ast_is_expression(primary_expression)) {
    AstPrimaryExpressionRef data = ast_palloc(struct AstPrimaryExpression);
    data->primary_expression = primary_expression;
    self = ast_palloc(struct Ast);
    self->tag = AST_PRIMARY_EXPRESSION;
    self->data.primary_expression = data;
  }
  return self;
}

AstRef ast_make_postfix_expression(AstRef postfix) {
  AstRef self = NULL;
  if (ast_is_primary_expression(postfix) ||
      ast_is_array_subscript_expression(postfix) ||
      ast_is_function_call_expression(postfix) ||
      ast_is_member_access_expression(postfix) ||
      ast_is_member_access_through_pointer_expression(postfix) ||
      ast_is_postfix_increment_expression(postfix) ||
      ast_is_postfix_decrement_expression(postfix)) {
    AstPostfixExpressionRef data = ast_palloc(struct AstPostfixExpression);
    data->postfix = postfix;
    self = ast_palloc(struct Ast);
    self->tag = AST_POSTFIX_EXPRESSION;
    self->data.postfix_expression = data;
  }
  return self;
}

AstRef ast_make_array_subscript_expression(AstRef array, AstRef subscript) {
  AstRef self = NULL;
  if (ast_is_postfix_expression(array) &&
      ast_is_expression(subscript)) {
    AstArraySubscriptExpressionRef data =
        ast_palloc(struct AstArraySubscriptExpression);
    data->array = array;
    data->subscript = subscript;
    self = ast_palloc(struct Ast);
    self->tag = AST_ARRAY_SUBSCRIPT_EXPRESSION;
    self->data.array_subscript_expression = data;
  }
  return self;
}

AstRef ast_make_function_call_expression(
    AstRef function, AstRef argument_list) {
  AstRef self = NULL;
  if (ast_is_postfix_expression(function) &&
      ast_is_argument_expression_list(argument_list)) {
    AstFunctionCallExpressionRef data =
        ast_palloc(struct AstFunctionCallExpression);
    data->function = function;
    data->argument_list = argument_list;
    self = ast_palloc(struct Ast);
    self->tag = AST_FUNCTION_CALL_EXPRESSION;
    self->data.function_call_expression = data;
  }
  return self;
}

AstRef ast_make_member_access_expression(AstRef object, AstRef member) {
  AstRef self = NULL;
  if (ast_is_postfix_expression(object) &&
      ast_is_identifier(member)) {
    AstMemberAccessExpressionRef data =
        ast_palloc(struct AstMemberAccessExpression);
    data->object = object;
    data->member = member;
    self = ast_palloc(struct Ast);
    self->tag = AST_MEMBER_ACCESS_EXPRESSION;
    self->data.member_access_expression = data;
  }
  return self;
}

AstRef ast_make_member_access_through_pointer_expression(
    AstRef object, AstRef member) {
  AstRef self = NULL;
  if (ast_is_postfix_expression(object) &&
      ast_is_identifier(member)) {
    AstMemberAccessThroughPointerExpressionRef data =
        ast_palloc(struct AstMemberAccessThroughPointerExpression);
    data->object = object;
    data->member = member;
    self = ast_palloc(struct Ast);
    self->tag = AST_MEMBER_ACCESS_THROUGH_POINTER_EXPRESSION;
    self->data.member_access_through_pointer_expression = data;
  }
  return self;
}

AstRef ast_make_postfix_increment_expression(AstRef postfix) {
  AstRef self = NULL;
  if (ast_is_postfix_expression(postfix)) {
    AstPostfixIncrementExpressionRef data =
        ast_palloc(struct AstPostfixIncrementExpression);
    data->postfix = postfix;
    self = ast_palloc(struct Ast);
    self->tag = AST_POSTFIX_INCREMENT_EXPRESSION;
    self->data.postfix_increment_expression = data;
  }
  return self;
}

AstRef ast_make_postfix_decrement_expression(AstRef postfix) {
  AstRef self = NULL;
  if (ast_is_postfix_decrement_expression(postfix)) {
    AstPostfixDecrementExpressionRef data =
        ast_palloc(struct AstPostfixDecrementExpression);
    data->postfix = postfix;
    self = ast_palloc(struct Ast);
    self->tag = AST_POSTFIX_DECREMENT_EXPRESSION;
    self->data.postfix_decrement_expression = data;
  }
  return self;
}

AstRef ast_make_argument_expression_list(void) {
  AstRef self = NULL;
  AstArgumentExpressionListRef data =
      ast_palloc(struct AstArgumentExpressionList);
  data->argument_list = ast_make_vector();
  self = ast_palloc(struct Ast);
  self->tag = AST_ARGUMENT_EXPRESSION_LIST;
  self->data.argument_expression_list = data;
  return self;
}

AstRef ast_push_argument_expression_list(
    AstRef argument_list, AstRef argument) {
  AstRef self = NULL;
  if (ast_is_argument_expression_list(argument_list) &&
      ast_is_assignment_expression(argument)) {
    AstArgumentExpressionListRef list =
        ast_get_argument_expression_list(argument_list);
    ast_push_vector(list->argument_list, argument);
    self = argument_list;
  }
  return self;
}

AstRef ast_make_unary_expression(AstRef unary) {
  AstRef self = NULL;
  if (ast_is_postfix_expression(unary) ||
      ast_is_prefix_increment_expression(unary) ||
      ast_is_prefix_decrement_expression(unary) ||
      ast_is_address_of_expression(unary) ||
      ast_is_pointer_dereference_expression(unary) ||
      ast_is_unary_plus_expression(unary) ||
      ast_is_unary_minus_expression(unary) ||
      ast_is_bitwise_not_expression(unary) ||
      ast_is_logical_not_expression(unary) ||
      ast_is_sizeof_expression(unary) ||
      ast_is_sizeof_type_expression(unary)) {
    AstUnaryExpressionRef data = ast_palloc(struct AstUnaryExpression);
    data->unary = unary;
    self = ast_palloc(struct Ast);
    self->tag = AST_UNARY_EXPRESSION;
    self->data.unary_expression = data;
  }
  return self;
}

AstRef ast_make_prefix_increment_expression(AstRef unary) {
  AstRef self = NULL;
  if (ast_is_unary_expression(unary)) {
    AstPrefixIncrementExpressionRef data =
        ast_palloc(struct AstPrefixIncrementExpression);
    data->unary = unary;
    self = ast_palloc(struct Ast);
    self->tag = AST_PREFIX_INCREMENT_EXPRESSION;
    self->data.prefix_increment_expression = data;
  }
  return self;
}

AstRef ast_make_prefix_decrement_expression(AstRef unary) {
  AstRef self = NULL;
  if (ast_is_unary_expression(unary)) {
    AstPrefixDecrementExpressionRef data =
        ast_palloc(struct AstPrefixDecrementExpression);
    data->unary = unary;
    self = ast_palloc(struct Ast);
    self->tag = AST_PREFIX_DECREMENT_EXPRESSION;
    self->data.prefix_decrement_expression = data;
  }
  return self;
}

AstRef ast_make_address_of_expression(AstRef cast) {
  AstRef self = NULL;
  if (ast_is_cast_expression(cast)) {
    AstAddressOfExpressionRef data = ast_palloc(struct AstAddressOfExpression);
    data->cast = cast;
    self = ast_palloc(struct Ast);
    self->tag = AST_ADDRESS_OF_EXPRESSION;
    self->data.address_of_expression = data;
  }
  return self;
}

AstRef ast_make_pointer_dereference_expression(AstRef cast) {
  AstRef self = NULL;
  if (ast_is_cast_expression(cast)) {
    AstPointerDereferenceExpressionRef data =
        ast_palloc(struct AstPointerDereferenceExpression);
    data->cast = cast;
    self = ast_palloc(struct Ast);
    self->tag = AST_POINTER_DEREFERENCE_EXPRESSION;
    self->data.pointer_dereference_expression = data;
  }
  return self;
}

AstRef ast_make_unary_plus_expression(AstRef cast) {
  AstRef self = NULL;
  if (ast_is_cast_expression(cast)) {
    AstUnaryPlusExpressionRef data = ast_palloc(struct AstUnaryPlusExpression);
    data->cast = cast;
    self = ast_palloc(struct Ast);
    self->tag = AST_UNARY_PLUS_EXPRESSION;
    self->data.unary_plus_expression = data;
  }
  return self;
}

AstRef ast_make_unary_minus_expression(AstRef cast) {
  AstRef self = NULL;
  if (ast_is_cast_expression(cast)) {
    AstUnaryMinusExpressionRef data =
        ast_palloc(struct AstUnaryMinusExpression);
    data->cast = cast;
    self = ast_palloc(struct Ast);
    self->tag = AST_UNARY_MINUS_EXPRESSION;
    self->data.unary_minus_expression = data;
  }
  return self;
}

AstRef ast_make_bitwise_not_expression(AstRef cast) {
  AstRef self = NULL;
  if (ast_is_cast_expression(cast)) {
    AstBitwiseNotExpressionRef data =
        ast_palloc(struct AstBitwiseNotExpression);
    data->cast = cast;
    self = ast_palloc(struct Ast);
    self->tag = AST_BITWISE_NOT_EXPRESSION;
    self->data.bitwise_not_expression = data;
  }
  return self;
}

AstRef ast_make_logical_not_expression(AstRef cast) {
  AstRef self = NULL;
  if (ast_is_cast_expression(cast)) {
    AstLogicalNotExpressionRef data =
        ast_palloc(struct AstLogicalNotExpression);
    data->cast = cast;
    self = ast_palloc(struct Ast);
    self->tag = AST_LOGICAL_NOT_EXPRESSION;
    self->data.logical_not_expression = data;
  }
  return self;
}

AstRef ast_make_sizeof_expression(AstRef unary) {
  AstRef self = NULL;
  if (ast_is_unary_expression(unary)) {
    AstSizeofExpressionRef data = ast_palloc(struct AstSizeofExpression);
    data->unary = unary;
    self = ast_palloc(struct Ast);
    self->tag = AST_SIZEOF_EXPRESSION;
    self->data.sizeof_expression = data;
  }
  return self;
}

AstRef ast_make_sizeof_type_expression(AstRef type_name) {
  AstRef self = NULL;
  if (ast_is_type_name(type_name)) {
    AstSizeofTypeExpressionRef data =
        ast_palloc(struct AstSizeofTypeExpression);
    data->type_name = type_name;
    self = ast_palloc(struct Ast);
    self->tag = AST_SIZEOF_TYPE_EXPRESSION;
    self->data.sizeof_type_expression = data;
  }
  return self;
}

AstRef ast_make_cast_expression(AstRef cast) {
  AstRef self = NULL;
  if (ast_is_unary_expression(cast) ||
      ast_is_type_cast_expression(cast)) {
    AstCastExpressionRef data = ast_palloc(struct AstCastExpression);
    data->cast = cast;
    self = ast_palloc(struct Ast);
    self->tag = AST_CAST_EXPRESSION;
    self->data.cast_expression = data;
  }
  return self;
}

AstRef ast_make_type_cast_expression(AstRef type_name, AstRef expression) {
  AstRef self = NULL;
  if (ast_is_type_name(type_name) &&
      ast_is_cast_expression(expression)) {
    AstTypeCastExpressionRef data = ast_palloc(struct AstTypeCastExpression);
    data->type_name = type_name;
    data->expression = expression;
    self = ast_palloc(struct Ast);
    self->tag = AST_TYPE_CAST_EXPRESSION;
    self->data.type_cast_expression = data;
  }
  return self;
}

AstRef ast_make_multiplicative_expression(AstRef expression) {
  AstRef self = NULL;
  if (ast_is_cast_expression(expression) ||
      ast_is_product_expression(expression) ||
      ast_is_division_expression(expression) ||
      ast_is_modulo_expression(expression)) {
    AstMultiplicativeExpressionRef data =
        ast_palloc(struct AstMultiplicativeExpression);
    data->expression = expression;
    self = ast_palloc(struct Ast);
    self->tag = AST_MULTIPLICATIVE_EXPRESSION;
    self->data.multiplicative_expression = data;
  }
  return self;
}

AstRef ast_make_product_expression(AstRef multiplicative, AstRef cast) {
  AstRef self = NULL;
  if (ast_is_multiplicative_expression(multiplicative) &&
      ast_is_cast_expression(cast)) {
    AstProductExpressionRef data = ast_palloc(struct AstProductExpression);
    data->multiplicative = multiplicative;
    data->cast = cast;
    self = ast_palloc(struct Ast);
    self->tag = AST_PRODUCT_EXPRESSION;
    self->data.product_expression = data;
  }
  return self;
}

AstRef ast_make_division_expression(AstRef multiplicative, AstRef cast) {
  AstRef self = NULL;
  if (ast_is_multiplicative_expression(multiplicative) &&
      ast_is_cast_expression(cast)) {
    AstDivisionExpressionRef data = ast_palloc(struct AstDivisionExpression);
    data->multiplicative = multiplicative;
    data->cast = cast;
    self = ast_palloc(struct Ast);
    self->tag = AST_DIVISION_EXPRESSION;
    self->data.division_expression = data;
  }
  return self;
}

AstRef ast_make_modulo_expression(AstRef multiplicative, AstRef cast) {
  AstRef self = NULL;
  if (ast_is_multiplicative_expression(multiplicative) &&
      ast_is_cast_expression(cast)) {
    AstModuloExpressionRef data = ast_palloc(struct AstModuloExpression);
    data->multiplicative = multiplicative;
    data->cast = cast;
    self = ast_palloc(struct Ast);
    self->tag = AST_MODULO_EXPRESSION;
    self->data.modulo_expression = data;
  }
  return self;
}

AstRef ast_make_additive_expression(AstRef expression) {
  AstRef self = NULL;
  if (ast_is_multiplicative_expression(expression) ||
      ast_is_addition_expression(expression) ||
      ast_is_subtraction_expression(expression)) {
    AstAdditiveExpressionRef data = ast_palloc(struct AstAdditiveExpression);
    data->expression = expression;
    self = ast_palloc(struct Ast);
    self->tag = AST_ADDITIVE_EXPRESSION;
    self->data.additive_expression = data;
  }
  return self;
}

AstRef ast_make_addition_expression(AstRef additive, AstRef multiplicative) {
  AstRef self = NULL;
  if (ast_is_additive_expression(additive) &&
      ast_is_multiplicative_expression(multiplicative)) {
    AstAdditionExpressionRef data = ast_palloc(struct AstAdditionExpression);
    data->additive = additive;
    data->multiplicative = multiplicative;
    self = ast_palloc(struct Ast);
    self->tag = AST_ADDITION_EXPRESSION;
    self->data.addition_expression = data;
  }
  return self;
}

AstRef ast_make_subtraction_expression(AstRef additive, AstRef multiplicative) {
  AstRef self = NULL;
  if (ast_is_additive_expression(additive) &&
      ast_is_multiplicative_expression(multiplicative)) {
    AstSubtractionExpressionRef data =
        ast_palloc(struct AstSubtractionExpression);
    data->additive = additive;
    data->multiplicative = multiplicative;
    self = ast_palloc(struct Ast);
    self->tag = AST_SUBTRACTION_EXPRESSION;
    self->data.subtraction_expression = data;
  }
  return self;
}

AstRef ast_make_shift_expression(AstRef expression) {
  AstRef self = NULL;
  if (ast_is_additive_expression(expression) ||
      ast_is_left_shift_expression(expression) ||
      ast_is_right_shift_expression(expression)) {
    AstShiftExpressionRef data = ast_palloc(struct AstShiftExpression);
    data->expression = expression;
    self = ast_palloc(struct Ast);
    self->tag = AST_SHIFT_EXPRESSION;
    self->data.shift_expression = data;
  }
  return self;
}

AstRef ast_make_left_shift_expression(AstRef shift, AstRef additive) {
  AstRef self = NULL;
  if (ast_is_shift_expression(shift) &&
      ast_is_additive_expression(additive)) {
    AstLeftShiftExpressionRef data = ast_palloc(struct AstLeftShiftExpression);
    data->shift = shift;
    data->additive = additive;
    self = ast_palloc(struct Ast);
    self->tag = AST_LEFT_SHIFT_EXPRESSION;
    self->data.left_shift_expression = data;
  }
  return self;
}

AstRef ast_make_right_shift_expression(AstRef shift, AstRef additive) {
  AstRef self = NULL;
  if (ast_is_shift_expression(shift) &&
      ast_is_additive_expression(additive)) {
    AstRightShiftExpressionRef data =
        ast_palloc(struct AstRightShiftExpression);
    data->shift = shift;
    data->additive = additive;
    self = ast_palloc(struct Ast);
    self->tag = AST_RIGHT_SHIFT_EXPRESSION;
    self->data.right_shift_expression = data;
  }
  return self;
}

AstRef ast_make_relational_expression(AstRef expression) {
  AstRef self = NULL;
  if (ast_is_shift_expression(expression) ||
      ast_is_less_than_expression(expression) ||
      ast_is_greater_than_expression(expression) ||
      ast_is_less_than_or_equal_to_expression(expression) ||
      ast_is_greater_than_or_equal_to_expression(expression)) {
    AstRelationalExpressionRef data =
        ast_palloc(struct AstRelationalExpression);
    data->expression = expression;
    self = ast_palloc(struct Ast);
    self->tag = AST_RELATIONAL_EXPRESSION;
    self->data.relational_expression = data;
  }
  return self;
}

AstRef ast_make_less_than_expression(AstRef relational, AstRef shift) {
  AstRef self = NULL;
  if (ast_is_relational_expression(relational) &&
      ast_is_shift_expression(shift)) {
    AstLessThanExpressionRef data = ast_palloc(struct AstLessThanExpression);
    data->relational = relational;
    data->shift = shift;
    self = ast_palloc(struct Ast);
    self->tag = AST_LESS_THAN_EXPRESSION;
    self->data.less_than_expression = data;
  }
  return self;
}

AstRef ast_make_greater_than_expression(AstRef relational, AstRef shift) {
  AstRef self = NULL;
  if (ast_is_relational_expression(relational) &&
      ast_is_shift_expression(shift)) {
    AstGreaterThanExpressionRef data =
        ast_palloc(struct AstGreaterThanExpression);
    data->relational = relational;
    data->shift = shift;
    self = ast_palloc(struct Ast);
    self->tag = AST_GREATER_THAN_EXPRESSION;
    self->data.greater_than_expression = data;
  }
  return self;
}

AstRef ast_make_less_than_or_equal_to_expression(
    AstRef relational, AstRef shift) {
  AstRef self = NULL;
  if (ast_is_relational_expression(relational) &&
      ast_is_shift_expression(shift)) {
    AstLessThanOrEqualToExpressionRef data =
        ast_palloc(struct AstLessThanOrEqualToExpression);
    data->relational = relational;
    data->shift = shift;
    self = ast_palloc(struct Ast);
    self->tag = AST_LESS_THAN_OR_EQUAL_TO_EXPRESSION;
    self->data.less_than_or_equal_to_expression = data;
  }
  return self;
}

AstRef ast_make_greater_than_or_equal_to_expression(
    AstRef relational, AstRef shift) {
  AstRef self = NULL;
  if (ast_is_relational_expression(relational) &&
      ast_is_shift_expression(shift)) {
    AstGreaterThanOrEqualToExpressionRef data =
        ast_palloc(struct AstGreaterThanOrEqualToExpression);
    data->relational = relational;
    data->shift = shift;
    self = ast_palloc(struct Ast);
    self->tag = AST_GREATER_THAN_OR_EQUAL_TO_EXPRESSION;
    self->data.greater_than_or_equal_to_expression = data;
  }
  return self;
}

AstRef ast_make_equality_expression(AstRef expression) {
  AstRef self = NULL;
  if (ast_is_relational_expression(expression) ||
      ast_is_equal_to_expression(expression) ||
      ast_is_not_equal_to_expression(expression)) {
    AstEqualityExpressionRef data =
        ast_palloc(struct AstEqualityExpression);
    data->expression = expression;
    self = ast_palloc(struct Ast);
    self->tag = AST_EQUALITY_EXPRESSION;
    self->data.equality_expression = data;
  }
  return self;
}

AstRef ast_make_equal_to_expression(AstRef equality, AstRef relational) {
  AstRef self = NULL;
  if (ast_is_equality_expression(equality) &&
      ast_is_relational_expression(relational)) {
    AstEqualToExpressionRef data = ast_palloc(struct AstEqualToExpression);
    data->equality = equality;
    data->relational = relational;
    self = ast_palloc(struct Ast);
    self->tag = AST_EQUAL_TO_EXPRESSION;
    self->data.equal_to_expression = data;
  }
  return self;
}

AstRef ast_make_not_equal_to_expression(AstRef equality, AstRef relational) {
  AstRef self = NULL;
  if (ast_is_equality_expression(equality) &&
      ast_is_relational_expression(relational)) {
    AstNotEqualToExpressionRef data =
        ast_palloc(struct AstNotEqualToExpression);
    data->equality = equality;
    data->relational = relational;
    self = ast_palloc(struct Ast);
    self->tag = AST_NOT_EQUAL_TO_EXPRESSION;
    self->data.not_equal_to_expression = data;
  }
  return self;
}

AstRef ast_make_bitwise_and_expression(AstRef expression) {
  AstRef self = NULL;
  if (ast_is_equality_expression(expression) ||
      ast_is_bitwise_and_operator_expression(expression)) {
    AstBitwiseAndExpressionRef data =
        ast_palloc(struct AstBitwiseAndExpression);
    data->expression = expression;
    self = ast_palloc(struct Ast);
    self->tag = AST_BITWISE_AND_EXPRESSION;
    self->data.bitwise_and_expression = data;
  }
  return self;
}

AstRef ast_make_bitwise_and_operator_expression(
    AstRef bitwise_and, AstRef equality) {
  AstRef self = NULL;
  if (ast_is_bitwise_and_expression(bitwise_and) &&
      ast_is_equality_expression(equality)) {
    AstBitwiseAndOperatorExpressionRef data =
        ast_palloc(struct AstBitwiseAndOperatorExpression);
    data->bitwise_and = bitwise_and;
    data->equality = equality;
    self = ast_palloc(struct Ast);
    self->tag = AST_BITWISE_AND_OPERATOR_EXPRESSION;
    self->data.bitwise_and_operator_expression = data;
  }
  return self;
}

AstRef ast_make_bitwise_xor_expression(AstRef expression) {
  AstRef self = NULL;
  if (ast_is_bitwise_and_expression(expression) ||
      ast_is_bitwise_xor_operator_expression(expression)) {
    AstBitwiseXorExpressionRef data =
        ast_palloc(struct AstBitwiseXorExpression);
    data->expression = expression;
    self = ast_palloc(struct Ast);
    self->tag = AST_BITWISE_XOR_EXPRESSION;
    self->data.bitwise_xor_expression = data;
  }
  return self;
}

AstRef ast_make_bitwise_xor_operator_expression(
    AstRef bitwise_xor, AstRef bitwise_and) {
  AstRef self = NULL;
  if (ast_is_bitwise_xor_expression(bitwise_xor) &&
      ast_is_bitwise_and_expression(bitwise_and)) {
    AstBitwiseXorOperatorExpressionRef data =
        ast_palloc(struct AstBitwiseXorOperatorExpression);
    data->bitwise_xor = bitwise_xor;
    data->bitwise_and = bitwise_and;
    self = ast_palloc(struct Ast);
    self->tag = AST_BITWISE_XOR_OPERATOR_EXPRESSION;
    self->data.bitwise_xor_operator_expression = data;
  }
  return self;
}

AstRef ast_make_bitwise_or_expression(AstRef expression) {
  AstRef self = NULL;
  if (ast_is_bitwise_xor_expression(expression) ||
      ast_is_bitwise_or_operator_expression(expression)) {
    AstBitwiseOrExpressionRef data = ast_palloc(struct AstBitwiseOrExpression);
    data->expression = expression;
    self = ast_palloc(struct Ast);
    self->tag = AST_BITWISE_OR_EXPRESSION;
    self->data.bitwise_or_expression = data;
  }
  return self;
}

AstRef ast_make_bitwise_or_operator_expression(
    AstRef bitwise_or, AstRef bitwise_xor) {
  AstRef self = NULL;
  if (ast_is_bitwise_or_expression(bitwise_or) &&
      ast_is_bitwise_xor_expression(bitwise_xor)) {
    AstBitwiseOrOperatorExpressionRef data =
        ast_palloc(struct AstBitwiseOrOperatorExpression);
    data->bitwise_or = bitwise_or;
    data->bitwise_xor = bitwise_xor;
    self = ast_palloc(struct Ast);
    self->tag = AST_BITWISE_OR_OPERATOR_EXPRESSION;
    self->data.bitwise_or_operator_expression = data;
  }
  return self;
}

AstRef ast_make_logical_and_expression(AstRef expression) {
  AstRef self = NULL;
  if (ast_is_bitwise_or_expression(expression) ||
      ast_is_logical_and_operator_expression(expression)) {
    AstLogicalAndExpressionRef data =
        ast_palloc(struct AstLogicalAndExpression);
    data->expression = expression;
    self = ast_palloc(struct Ast);
    self->tag = AST_LOGICAL_AND_EXPRESSION;
    self->data.logical_and_expression = data;
  }
  return self;
}

AstRef ast_make_logical_and_operator_expression(
    AstRef logical_and, AstRef bitwise_or) {
  AstRef self = NULL;
  if (ast_is_logical_and_expression(logical_and) &&
      ast_is_bitwise_or_expression(bitwise_or)) {
    AstLogicalAndOperatorExpressionRef data =
        ast_palloc(struct AstLogicalAndOperatorExpression);
    data->logical_and = logical_and;
    data->bitwise_or = bitwise_or;
    self = ast_palloc(struct Ast);
    self->tag = AST_LOGICAL_AND_OPERATOR_EXPRESSION;
    self->data.logical_and_operator_expression = data;
  }
  return self;
}

AstRef ast_make_logical_or_expression(AstRef expression) {
  AstRef self = NULL;
  if (ast_is_logical_and_expression(expression) ||
      ast_is_logical_or_operator_expression(expression)) {
    AstLogicalOrExpressionRef data = ast_palloc(struct AstLogicalOrExpression);
    data->expression = expression;
    self = ast_palloc(struct Ast);
    self->tag = AST_LOGICAL_OR_EXPRESSION;
    self->data.logical_or_expression = data;
  }
  return self;
}

AstRef ast_make_logical_or_operator_expression(
    AstRef logical_or, AstRef logical_and) {
  AstRef self = NULL;
  if (ast_is_logical_or_expression(logical_or) &&
      ast_is_logical_and_expression(logical_and)) {
    AstLogicalOrOperatorExpressionRef data =
        ast_palloc(struct AstLogicalOrOperatorExpression);
    data->logical_or = logical_or;
    data->logical_and = logical_and;
    self = ast_palloc(struct Ast);
    self->tag = AST_LOGICAL_OR_OPERATOR_EXPRESSION;
    self->data.logical_or_operator_expression = data;
  }
  return self;
}

AstRef ast_make_conditional_expression(AstRef expression) {
  AstRef self = NULL;
  if (ast_is_logical_or_expression(expression) ||
      ast_is_conditional_operator_expression(expression)) {
    AstConditionalExpressionRef data =
        ast_palloc(struct AstConditionalExpression);
    data->expression = expression;
    self = ast_palloc(struct Ast);
    self->tag = AST_CONDITIONAL_EXPRESSION;
    self->data.conditional_expression = data;
  }
  return self;
}

AstRef ast_make_conditional_operator_expression(
    AstRef logical_or, AstRef expression, AstRef conditional) {
  AstRef self = NULL;
  if (ast_is_logical_or_expression(logical_or) &&
      ast_is_expression(expression) &&
      ast_is_conditional_expression(conditional)) {
    AstConditionalOperatorExpressionRef data =
        ast_palloc(struct AstConditionalOperatorExpression);
    data->logical_or = logical_or;
    data->expression = expression;
    data->conditional = conditional;
    self = ast_palloc(struct Ast);
    self->tag = AST_CONDITIONAL_OPERATOR_EXPRESSION;
    self->data.conditional_operator_expression = data;
  }
  return self;
}

AstRef ast_make_assignment_expression(AstRef expression) {
  AstRef self = NULL;
  if (ast_is_conditional_expression(expression) ||
      ast_is_basic_assignment_expression(expression) ||
      ast_is_multiplication_assignment_expression(expression) ||
      ast_is_division_assignment_expression(expression) ||
      ast_is_modulo_assignment_expression(expression) ||
      ast_is_addition_assignment_expression(expression) ||
      ast_is_subtraction_assignment_expression(expression) ||
      ast_is_left_shift_assignment_expression(expression) ||
      ast_is_right_shift_assignment_expression(expression) ||
      ast_is_bitwise_and_assignment_expression(expression) ||
      ast_is_bitwise_xor_assignment_expression(expression) ||
      ast_is_bitwise_or_assignment_expression(expression)) {
    AstAssignmentExpressionRef data =
        ast_palloc(struct AstAssignmentExpression);
    data->expression = expression;
    self = ast_palloc(struct Ast);
    self->tag = AST_ASSIGNMENT_EXPRESSION;
    self->data.assignment_expression = data;
  }
  return self;
}

AstRef ast_make_basic_assignment_expression(AstRef unary, AstRef assignment) {
  AstRef self = NULL;
  if (ast_is_unary_expression(unary) &&
      ast_is_assignment_expression(assignment)) {
    AstBasicAssignmentExpressionRef data =
        ast_palloc(struct AstBasicAssignmentExpression);
    data->unary = unary;
    data->assignment = assignment;
    self = ast_palloc(struct Ast);
    self->tag = AST_BASIC_ASSIGNMENT_EXPRESSION;
    self->data.basic_assignment_expression = data;
  }
  return self;
}

AstRef ast_make_multiplication_assignment_expression(
    AstRef unary, AstRef assignment) {
  AstRef self = NULL;
  if (ast_is_unary_expression(unary) &&
      ast_is_assignment_expression(assignment)) {
    AstMultiplicationAssignmentExpressionRef data =
        ast_palloc(struct AstMultiplicationAssignmentExpression);
    data->unary = unary;
    data->assignment = assignment;
    self = ast_palloc(struct Ast);
    self->tag = AST_MULTIPLICATION_ASSIGNMENT_EXPRESSION;
    self->data.multiplication_assignment_expression = data;
  }
  return self;
}

AstRef ast_make_division_assignment_expression(
    AstRef unary, AstRef assignment) {
  AstRef self = NULL;
  if (ast_is_unary_expression(unary) &&
      ast_is_assignment_expression(assignment)) {
    AstDivisionAssignmentExpressionRef data =
        ast_palloc(struct AstDivisionAssignmentExpression);
    data->unary = unary;
    data->assignment = assignment;
    self = ast_palloc(struct Ast);
    self->tag = AST_DIVISION_ASSIGNMENT_EXPRESSION;
    self->data.division_assignment_expression = data;
  }
  return self;
}

AstRef ast_make_modulo_assignment_expression(AstRef unary, AstRef assignment) {
  AstRef self = NULL;
  if (ast_is_unary_expression(unary) &&
      ast_is_assignment_expression(assignment)) {
    AstModuloAssignmentExpressionRef data =
        ast_palloc(struct AstModuloAssignmentExpression);
    data->unary = unary;
    data->assignment = assignment;
    self = ast_palloc(struct Ast);
    self->tag = AST_MODULO_ASSIGNMENT_EXPRESSION;
    self->data.modulo_assignment_expression = data;
  }
  return self;
}

AstRef ast_make_addition_assignment_expression(
    AstRef unary, AstRef assignment) {
  AstRef self = NULL;
  if (ast_is_unary_expression(unary) &&
      ast_is_assignment_expression(assignment)) {
    AstAdditionAssignmentExpressionRef data =
        ast_palloc(struct AstAdditionAssignmentExpression);
    data->unary = unary;
    data->assignment = assignment;
    self = ast_palloc(struct Ast);
    self->tag = AST_ADDITION_ASSIGNMENT_EXPRESSION;
    self->data.addition_assignment_expression = data;
  }
  return self;
}

AstRef ast_make_subtraction_assignment_expression(
    AstRef unary, AstRef assignment) {
  AstRef self = NULL;
  if (ast_is_unary_expression(unary) &&
      ast_is_assignment_expression(assignment)) {
    AstSubtractionAssignmentExpressionRef data =
        ast_palloc(struct AstSubtractionAssignmentExpression);
    data->unary = unary;
    data->assignment = assignment;
    self = ast_palloc(struct Ast);
    self->tag = AST_SUBTRACTION_ASSIGNMENT_EXPRESSION;
    self->data.subtraction_assignment_expression = data;
  }
  return self;
}

AstRef ast_make_left_shift_assignment_expression(
    AstRef unary, AstRef assignment) {
  AstRef self = NULL;
  if (ast_is_unary_expression(unary) &&
      ast_is_assignment_expression(assignment)) {
    AstLeftShiftAssignmentExpressionRef data =
        ast_palloc(struct AstLeftShiftAssignmentExpression);
    data->unary = unary;
    data->assignment = assignment;
    self = ast_palloc(struct Ast);
    self->tag = AST_LEFT_SHIFT_ASSIGNMENT_EXPRESSION;
    self->data.left_shift_assignment_expression = data;
  }
  return self;
}

AstRef ast_make_right_shift_assignment_expression(
    AstRef unary, AstRef assignment) {
  AstRef self = NULL;
  if (ast_is_unary_expression(unary) &&
      ast_is_assignment_expression(assignment)) {
    AstRightShiftAssignmentExpressionRef data =
        ast_palloc(struct AstRightShiftAssignmentExpression);
    data->unary = unary;
    data->assignment = assignment;
    self = ast_palloc(struct Ast);
    self->tag = AST_RIGHT_SHIFT_ASSIGNMENT_EXPRESSION;
    self->data.right_shift_assignment_expression = data;
  }
  return self;
}

AstRef ast_make_bitwise_and_assignment_expression(
    AstRef unary, AstRef assignment) {
  AstRef self = NULL;
  if (ast_is_unary_expression(unary) &&
      ast_is_assignment_expression(assignment)) {
    AstBitwiseAndAssignmentExpressionRef data =
        ast_palloc(struct AstBitwiseAndAssignmentExpression);
    data->unary = unary;
    data->assignment = assignment;
    self = ast_palloc(struct Ast);
    self->tag = AST_BITWISE_AND_ASSIGNMENT_EXPRESSION;
    self->data.bitwise_and_assignment_expression = data;
  }
  return self;
}

AstRef ast_make_bitwise_xor_assignment_expression(
    AstRef unary, AstRef assignment) {
  AstRef self = NULL;
  if (ast_is_unary_expression(unary) &&
      ast_is_assignment_expression(assignment)) {
    AstBitwiseXorAssignmentExpressionRef data =
        ast_palloc(struct AstBitwiseXorAssignmentExpression);
    data->unary = unary;
    data->assignment = assignment;
    self = ast_palloc(struct Ast);
    self->tag = AST_BITWISE_XOR_ASSIGNMENT_EXPRESSION;
    self->data.bitwise_xor_assignment_expression = data;
  }
  return self;
}

AstRef ast_make_bitwise_or_assignment_expression(
    AstRef unary, AstRef assignment) {
  AstRef self = NULL;
  if (ast_is_unary_expression(unary) &&
      ast_is_assignment_expression(assignment)) {
    AstBitwiseOrAssignmentExpressionRef data =
        ast_palloc(struct AstBitwiseOrAssignmentExpression);
    data->unary = unary;
    data->assignment = assignment;
    self = ast_palloc(struct Ast);
    self->tag = AST_BITWISE_OR_ASSIGNMENT_EXPRESSION;
    self->data.bitwise_or_assignment_expression = data;
  }
  return self;
}

AstRef ast_make_expression(AstRef expression) {
  AstRef self = NULL;
  if (ast_is_assignment_expression(expression) ||
      ast_is_comma_expression(expression)) {
    AstExpressionRef data = ast_palloc(struct AstExpression);
    data->expression = expression;
    self = ast_palloc(struct Ast);
    self->tag = AST_EXPRESSION;
    self->data.expression = data;
  }
  return self;
}

AstRef ast_make_comma_expression(AstRef expression, AstRef assignment) {
  AstRef self = NULL;
  if (ast_is_expression(expression) &&
      ast_is_assignment_expression(expression)) {
    AstCommaExpressionRef data = ast_palloc(struct AstCommaExpression);
    data->expression = expression;
    data->assignment = assignment;
    self = ast_palloc(struct Ast);
    self->tag = AST_COMMA_EXPRESSION;
    self->data.comma_expression = data;
  }
  return self;
}

AstRef ast_make_constant_expression(AstRef conditional) {
  AstRef self = NULL;
  if (ast_is_conditional_expression(conditional)) {
    AstConstantExpressionRef data = ast_palloc(struct AstConstantExpression);
    data->conditional = conditional;
    self = ast_palloc(struct Ast);
    self->tag = AST_CONSTANT_EXPRESSION;
    self->data.constant_expression = data;
  }
  return self;
}
