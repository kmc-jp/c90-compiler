#include "expressions.h"
#include "ast_impl.h"
#include "is_method.h"
#include "pool.h"

struct AstPrimaryExpression {
};

struct AstPostfixExpression {
  AstRef postfix;
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
