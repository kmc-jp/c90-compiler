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
