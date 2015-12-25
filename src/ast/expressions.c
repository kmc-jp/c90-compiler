#include "expressions.h"
#include "ast_impl.h"
#include "is_method.h"
#include "get_method.h"
#include "pool.h"

struct AstPrimaryExpression {
  AstRef primary_expression;
};

struct AstPostfixExpression {
  AstRef postfix;
};

struct AstArraySubscriptExpression {
  AstRef array;
  AstRef subscript;
};

struct AstFunctionCallExpression {
  AstRef function;
  AstRef argument_list;
};

struct AstMemberAccessExpression {
  AstRef object;
  AstRef member;
};

struct AstMemberAccessThroughPointerExpression {
  AstRef object;
  AstRef member;
};

struct AstPostfixIncrementExpression {
  AstRef postfix;
};

struct AstPostfixDecrementExpression {
  AstRef postfix;
};

struct AstArgumentExpressionList {
  AstVectorRef argument_list;
};

struct AstUnaryExpression {
  AstRef unary;
};

struct AstPrefixIncrementExpression {
  AstRef unary;
};

struct AstPrefixDecrementExpression {
  AstRef unary;
};

struct AstAddressOfExpression {
  AstRef cast;
};

struct AstPointerDereferenceExpression {
  AstRef cast;
};

struct AstUnaryPlusExpression {
  AstRef cast;
};

struct AstUnaryMinusExpression {
  AstRef cast;
};

struct AstBitwiseNotExpression {
  AstRef cast;
};

struct AstLogicalNotExpression {
  AstRef cast;
};

struct AstSizeofExpression {
  AstRef unary;
};

struct AstSizeofTypeExpression {
  AstRef type_name;
};

struct AstCastExpression {
};

struct AstTypeCastExpression {
};

struct AstMultiplicativeExpression {
};

struct AstProductExpression {
};

struct AstDivisionExpression {
};

struct AstModuloExpression {
};

struct AstAdditiveExpression {
  AstRef expression;
};

struct AstAdditionExpression {
  AstRef additive;
  AstRef multiplicative;
};

struct AstSubtractionExpression {
  AstRef additive;
  AstRef multiplicative;
};

struct AstShiftExpression {
};

struct AstLeftShiftExpression {
};

struct AstRightShiftExpression {
};

struct AstRelationalExpression {
};

struct AstLessThanExpression {
};

struct AstGreaterThanExpression {
};

struct AstLessThanOrEqualToExpression {
};

struct AstGreaterThanOrEqualToExpression {
};

struct AstEqualityExpression {
};

struct AstEqualToExpression {
};

struct AstNotEqualToExpression {
};

struct AstBitwiseAndExpression {
};

struct AstBitwiseAndOperatorExpression {
};

struct AstBitwiseXorExpression {
};

struct AstBitwiseXorOperatorExpression {
};

struct AstBitwiseOrExpression {
};

struct AstBitwiseOrOperatorExpression {
};

struct AstLogicalAndExpression {
};

struct AstLogicalAndOperatorExpression {
};

struct AstLogicalOrExpression {
};

struct AstLogicalOrOperatorExpression {
};

struct AstConditionalExpression {
};

struct AstConditionalOperatorExpression {
};

struct AstAssignmentExpression {
};

struct AstBasicAssignmentExpression {
};

struct AstMultiplicationAssignmentExpression {
};

struct AstDivisionAssignmentExpression {
};

struct AstModuloAssignmentExpression {
};

struct AstAdditionAssignmentExpression {
};

struct AstSubtractionAssignmentExpression {
};

struct AstLeftShiftAssignmentExpression {
};

struct AstRightShiftAssignmentExpression {
};

struct AstBitwiseAndAssignmentExpression {
};

struct AstBitwiseXorAssignmentExpression {
};

struct AstBitwiseOrAssignmentExpression {
};

struct AstExpression {
};

struct AstCommaExpression {
};

struct AstConstantExpression {
};

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
