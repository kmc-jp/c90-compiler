#include "expressions.h"
#include "ast_impl.h"
#include "is_method.h"
#include "pool.h"

struct AstPrimaryExpression {
};

struct AstPostfixExpression {
};

struct AstArraySubscriptExpression {
};

struct AstFunctionCallExpression {
};

struct AstMemberAccessExpression {
};

struct AstMemberAccessThroughPointerExpression {
};

struct AstPostfixIncrementExpression {
};

struct AstPostfixDecrementExpression {
};

struct AstArgumentExpressionList {
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
};

struct AstUnaryMinusExpression {
};

struct AstBitwiseNotExpression {
};

struct AstLogicalNotExpression {
};

struct AstSizeofExpression {
};

struct AstSizeofTypeExpression {
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
};

struct AstAdditionExpression {
};

struct AstSubtractionExpression {
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
