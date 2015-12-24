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
};

struct AstPrefixIncrementExpression {
};

struct AstPrefixDecrementExpression {
};

struct AstAddressOfExpression {
};

struct AstPointerDereferenceExpression {
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
  AstRef expression;
};

struct AstProductExpression {
  AstRef multiplicative;
  AstRef cast;
};

struct AstDivisionExpression {
  AstRef multiplicative;
  AstRef cast;
};

struct AstModuloExpression {
  AstRef multiplicative;
  AstRef cast;
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
